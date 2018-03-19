#include "http_config.h"
#include "http_common.h"
#include "http_file.h"
#include "http_net.h"
#include "http_request_parser.h"
#include "http_SSI_replacer.h"
#include "http_response.h"
#include "http_server.h"
#include "http_cgi.h"
#include "string.h"

/*this connection is a per-connection server
    precondition: 
        - netops and fops should have been registered
        - file system should be mounted and files should be registered
*/

static int http_server_send404(HTTP_response_headerRequest_t *httpResponse, int socket, http_net_netops_t *netops)
{
    httpResponse->responseCode = HTTP_RESCODE_cerrorNotfound;
    int retBufLen = http_response_response_header(*httpResponse);

    //check retval write and disconnect
    if (retBufLen <= 0)
    {
        PRINT_ERROR("error forming 404 header (%d)\r\n", retBufLen);
        return -1;
    }
    netops->http_net_write(socket, (unsigned char *)httpResponse->headerBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS);
    netops->http_net_disconnect(socket);
    return 0;
}

static int http_server_send_serverError500(HTTP_response_headerRequest_t *httpResponse, int socket, http_net_netops_t *netops)
{
    httpResponse->responseCode = HTTP_RESCODE_serrorInternalerror;
    int retBufLen = http_response_response_header(*httpResponse);

    //check retval write and disconnect
    if (retBufLen <= 0)
    {
        PRINT_ERROR("error forming 500 header (%d)\r\n", retBufLen);
        return -1;
    }
    netops->http_net_write(socket, (unsigned char *)httpResponse->headerBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS);
    netops->http_net_disconnect(socket);
    return 0;
}

//helper function to find and replace a string . This function will overwrite contents of the original input buffer.
//So, make sure there is enough space left to process the replacement.
//returns number of replacements done.
static int http_server_findNreplace(char *buffer, int bufferLen, char *find, char *replace)
{
    int count = 0;

    //null terminate the buffer before proceeding. This should have been done at the source as well.
    buffer[bufferLen] = 0;
    unsigned int replaceLen = strlen(replace);
    unsigned int findLen = strlen(find);

    char *position = 0;
    do
    {
        //find occurrance of the string
        position = strstr(buffer, find);
        if (NULL == position)
            return count;
        sprintf(position, "%s%s", replace, position + findLen);
        position += replaceLen; //to avoid recurssive replace
        count++;
    } while (strlen(position) > findLen); //do while there is still more content left in the buffer

    return count;
}

static int http_server_writeChunkedBody(int socket, char *buffer, int length, http_net_netops_t *netops)
{
    char chunkedHeader[20];
    sprintf(chunkedHeader, "%04X\r\n", length);
    //write size
    netops->http_net_write(socket, (unsigned char *)chunkedHeader, strlen(chunkedHeader), HTTP_SERVER_TIMOUT_MS);
    //write contents
    netops->http_net_write(socket, (unsigned char *)buffer, length, HTTP_SERVER_TIMOUT_MS);
    netops->http_net_write(socket, (unsigned char *)"\r\n", 2, HTTP_SERVER_TIMOUT_MS);
    return 0;
}

static int http_server_findNseekBack(char *buffer, void *fp)
{
    int bufferLen = strlen(buffer) - 1; //0 indexed buffer length
    if (buffer[bufferLen] == '<')
    {
        http_file_fops.fseek(fp, -1, SEEK_END);
        buffer[bufferLen] = '\0';
    }
    else if (strcmp(&(buffer[bufferLen - 1]), "<-"))
    {
        http_file_fops.fseek(fp, -2, SEEK_END);
        buffer[bufferLen - 1] = '\0';
    }
    else if (strcmp(&(buffer[bufferLen - 2]), "<--"))
    {
        http_file_fops.fseek(fp, -3, SEEK_END);
        buffer[bufferLen - 2] = '\0';
    }
    else if (strcmp(&(buffer[bufferLen - 3]), "<--#"))
    {
        http_file_fops.fseek(fp, -4, SEEK_END);
        buffer[bufferLen - 3] = '\0';
    }
    else
    {
        char *position = 0, *pPosition = 0;
        do
        {
            pPosition = position;
            position = strstr(buffer, "<!--#");
        } while (NULL != position);

        if (NULL != pPosition)
        {
            unsigned int pPositionIndex=(buffer-pPosition);
            if(NULL!=strstr(pPosition+5,"#-->")){
                return 0;
            }
            else{
                http_file_fops.fseek(fp, (0 - pPositionIndex), SEEK_END);
            }
        }
    }
    return 0;
}

int http_server(int socket, http_net_netops_t *netops)
{
    unsigned char httpReadBuffer[HTTP_SERVER_READ_BUFFER_SIZE];
    char httpHeaderBuffer[HTTP_SERVER_HEADER_BUFFER_SIZE];
    if ((NULL == netops->http_net_read) || (NULL == netops->http_net_write))
    {
        PRINT_ERROR("netops read not initialized(%s)\r\n", "nullNetops");
        return -1;
    }
	//read one byte less to null terminate and make a string out of it.
    int byteCount = netops->http_net_read(socket, (unsigned char *)&httpReadBuffer, HTTP_SERVER_READ_BUFFER_SIZE-1, HTTP_SERVER_TIMOUT_MS);
    if (byteCount <= 0)
    {
        PRINT_ERROR("netops read timedout(%d)\r\n", byteCount);
        return -1; //most probably a timeout error to read from client
    }
	httpReadBuffer[byteCount]=0;
    //now the request headers are in buffer. time to parse the request
    http_request_t http_request;
    parseRquest_identifyRequest(httpReadBuffer, &http_request);
    void *fp;
    int retBufLen = 0;
    HTTP_response_headerRequest_t httpResponse;
    http_response_initReponseStruct(&httpResponse);
    httpResponse.headerBuffer = (char *)&httpHeaderBuffer;
    httpResponse.bufferLength = HTTP_SERVER_HEADER_BUFFER_SIZE;

    switch (http_request.method)
    {
    case GET:
        switch (http_request.fileClass)
        {
        case httpFileClass_none: //regular File processing flow
            if (NULL != http_file_fops.fopen)
            { //else FS is not mounted
                fp = http_file_fops.fopen(http_request.httpFilePath);
            }
            else
            {
                PRINT_ERROR("fops not mounted(%d)\r\n", httpFileClass_none);
                fp = NULL;
            }
            if (NULL == fp)
            { //file not found due to missing file or missing FS
                int retval = http_server_send404(&httpResponse, socket, netops);
                if (retval < 0)
                {
                    PRINT_ERROR("error forming 404 header (%d)\r\n", retval);
                    return -1;
                }
                return 0;
            }
            else
            { //file found . do read, determine if chunking is required, write accordingly and disconnect
                char freadBuffer[HTTP_SERVER_FREAD_BUFFER_SIZE];
                int readLen = http_file_fops.fread(&freadBuffer, sizeof(freadBuffer), 1, fp);
                if (http_file_fops.eof(fp))
                {                                                            //complete contents has been read to buffer. no chunking required
                    httpResponse.responseCode = HTTP_RESCODE_successSuccess; //200 OK
                    httpResponse.bodyLength = readLen;
                    httpResponse.filePath = http_request.httpFilePath;
                    retBufLen = http_response_response_header(httpResponse);
                    //check retval write and disconnect
                    if (retBufLen <= 0)
                    {
                        PRINT_ERROR("error forming 200 header (%d)\r\n", retBufLen);
                        return -1;
                    }
                    netops->http_net_write(socket, (unsigned char *)httpHeaderBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS); //write header
                    netops->http_net_write(socket, (unsigned char *)freadBuffer, readLen, HTTP_SERVER_TIMOUT_MS);        //
                    netops->http_net_disconnect(socket);
                    return 0;
                }
                else
                {                                                            //time to do chunked encoding
                    httpResponse.responseCode = HTTP_RESCODE_successSuccess; //200 OK
                    httpResponse.bodyLength = 0;
                    httpResponse.transferEncoding = transferEnc_chunked; //set chunked encoding since we dont know actual length yet
                    httpResponse.filePath = http_request.httpFilePath;   //path to be used for contentType
                    retBufLen = http_response_response_header(httpResponse);
                    //check retval write and disconnect
                    if (retBufLen <= 0)
                    {
                        PRINT_ERROR("error forming 200 header (%d)\r\n", retBufLen);
                        return -1;
                    }
                    //send out the response header
                    netops->http_net_write(socket, (unsigned char *)httpHeaderBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS); //write header

                    http_server_writeChunkedBody(socket, (char *)freadBuffer, readLen, netops);
                    do
                    { //now read and write remaining contents
                        readLen = http_file_fops.fread(&freadBuffer, sizeof(freadBuffer), 1, fp);
                        http_server_writeChunkedBody(socket, (char *)freadBuffer, readLen, netops);
                    } while (!http_file_fops.eof(fp));

                    //send last 0\r\n\r\n
                    netops->http_net_write(socket, (unsigned char *)"0\r\n\r\n", 5, HTTP_SERVER_TIMOUT_MS);
                    netops->http_net_disconnect(socket);
                }
            }
            break;
        case httpFileClass_SSI:
        {
            if (NULL != http_file_fops.fopen)
            { //else FS is not mounted
                fp = http_file_fops.fopen(http_request.httpFilePath);
            }
            else
            {
                PRINT_ERROR("fops not mounted(%d)\r\n", httpFileClass_none);
                fp = NULL;
            }
            if (NULL == fp)
            { //file not found due to missing file or missing FS
                int retval = http_server_send404(&httpResponse, socket, netops);
                if (retval < 0)
                {
                    PRINT_ERROR("error forming 404 header (%d)\r\n", retval);
                    return -1;
                }
                return 0;
            }
            else
            { //file found . do read, determine if chunking is required, write accordingly and disconnect
                char freadBuffer[HTTP_SERVER_FREAD_BUFFER_SIZE];

                //****inefficient and probably error inducing mechanism to process SSI replacement follows
                struct
                {
                    char SSIString[HTTP_MAX_SSI_LENGTH + 12]; //string and <!--##-->
                    char SSIReplacementString[HTTP_MAX_SSI_REPLACE_LENGTH];
                } ssiReplacements[HTTP_MAX_SSI_COUNT];

                int ssiCount = 0;
                //compute all replacement string irrespective of occurrence. optimize by computing only required strings
                //this has to be computed ahead of time to avoid the replacement strings changing while we process this in server
                int i = 0;
                for (i = 0; i < HTTP_MAX_SSI_COUNT; i++)
                { //iterate through the http_SSI_replacer to look for registered strings
                    if (NULL != http_SSI_replacer[i].SSI_String)
                    {
                        snprintf(ssiReplacements[ssiCount].SSIString, (HTTP_MAX_SSI_LENGTH + 12), "<!--#%s#-->", http_SSI_replacer[i].SSI_String);
                        http_SSI_get_replacer_string(http_SSI_replacer[i].SSI_String, ssiReplacements[ssiCount].SSIReplacementString, HTTP_MAX_SSI_REPLACE_LENGTH);
                        if (HTTP_MAX_SSI_LENGTH > strlen(ssiReplacements[ssiCount].SSIString))
                        {
                            //should we sned a server error here???
                            PRINT_ERROR("registered SSI string is larger than HTTP_MAX_SSI_LENGTH. replacements might be messed up. increase HTTP_MAX_SSI_LENGTH in config (%d)\r\n", (int)strlen(ssiReplacements[ssiCount].SSIString));
                        }
                        if (HTTP_MAX_SSI_REPLACE_LENGTH < strlen(http_SSI_replacer[i].SSI_String))
                        {
                            PRINT_ERROR("replacement string for %s is larger than HTTP_MAX_SSI_REPLACE_LENGTH. modify config to avoid partial replacement\r\n", http_SSI_replacer[i].SSI_String);
                        }
                        ssiCount++;
                    }
                }

                //populating only half the buffer to have space for replacements.
                //leaving last location for null terminating so that we can process it as a string
                int readLen = http_file_fops.fread(&freadBuffer, (HTTP_SERVER_FREAD_BUFFER_SIZE / 2) - 1, 1, fp);
                freadBuffer[readLen] = 0;
                if (http_file_fops.eof(fp))
                { //complete contents has been read to buffer. no chunking required
                    for (i = 0; i < ssiCount; i++)
                    { //search and replace all occurrences of the SSI string with replacement contens
                        http_server_findNreplace((char *)&freadBuffer, HTTP_SERVER_FREAD_BUFFER_SIZE, ssiReplacements[i].SSIString, ssiReplacements[i].SSIReplacementString);
                    }

                    //form the header, and write header followed by processed contents
                    httpResponse.responseCode = HTTP_RESCODE_successSuccess; //200 OK
                    httpResponse.bodyLength = strlen(freadBuffer);
                    httpResponse.filePath = http_request.httpFilePath;
                    retBufLen = http_response_response_header(httpResponse);
                    //check retval write and disconnect
                    if (retBufLen <= 0)
                    {
                        PRINT_ERROR("error forming 200 header (%d)\r\n", retBufLen);
                        return -1;
                    }
                    netops->http_net_write(socket, (unsigned char *)httpHeaderBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS); //write header
                    //now write the modified contents file into netstream
                    netops->http_net_write(socket, (unsigned char *)freadBuffer, httpResponse.bodyLength, HTTP_SERVER_TIMOUT_MS); //
                    netops->http_net_disconnect(socket);
                    return 0;
                }
                else
                {                                                            //time to do chunking
                    httpResponse.responseCode = HTTP_RESCODE_successSuccess; //200 OK
                    httpResponse.bodyLength = 0;
                    httpResponse.transferEncoding = transferEnc_chunked; //set chunked encoding since we dont know actual length yet
                    httpResponse.filePath = http_request.httpFilePath;   //path to be used for contentType
                    retBufLen = http_response_response_header(httpResponse);
                    //check retval write and disconnect
                    if (retBufLen <= 0)
                    {
                        PRINT_ERROR("error forming 200 header (%d)\r\n", retBufLen);
                        return -1;
                    }
                    //send out the response header
                    netops->http_net_write(socket, (unsigned char *)httpHeaderBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS); //write header

                    //search for partial SSI strings and seek back to read in next round
                    http_server_findNseekBack((char *)freadBuffer, fp);

                    //now do the replacement in buffer
                    for (i = 0; i < ssiCount; i++)
                    { //search and replace all occurrences of the SSI string with replacement contens
                        http_server_findNreplace((char *)&freadBuffer, HTTP_SERVER_FREAD_BUFFER_SIZE, ssiReplacements[i].SSIString, ssiReplacements[i].SSIReplacementString);
                    }
                    int repBufLength = strlen(freadBuffer);
                    //first write the contents we have read already
                    http_server_writeChunkedBody(socket, freadBuffer, repBufLength, netops);
                    do
                    { //now read and write remaining contents
                        readLen = http_file_fops.fread(&freadBuffer, (HTTP_SERVER_FREAD_BUFFER_SIZE / 2) - 1, 1, fp);
                        freadBuffer[readLen] = 0;

                        //search for incomplete comment in teh end and do a seek
                        //now do the replacement in buffer
                        for (i = 0; i < ssiCount; i++)
                        { //search and replace all occurrences of the SSI string with replacement contens
                            http_server_findNreplace((char *)&freadBuffer, HTTP_SERVER_FREAD_BUFFER_SIZE, ssiReplacements[i].SSIString, ssiReplacements[i].SSIReplacementString);
                        }
                        repBufLength = strlen(freadBuffer);

                        http_server_writeChunkedBody(socket, freadBuffer, repBufLength, netops);
                    } while (!http_file_fops.eof(fp));					

                    //send last 0\r\n\r\n
                    netops->http_net_write(socket, (unsigned char *)"0\r\n\r\n", 5, HTTP_SERVER_TIMOUT_MS);
                    netops->http_net_disconnect(socket);
                }
            }
        }
        break;
        case httpFileClass_CGI:
        { //no suport for chunked CGI output
            http_CGI_pathFunctionHandle_t cgiPathFunctionHandle = 0;
            cgiPathFunctionHandle = http_CGI_get_pathFunctionHandle(http_request.httpFilePath);
            if (NULL == cgiPathFunctionHandle)
            { //404 case
                int retval = http_server_send404(&httpResponse, socket, netops);
                if (retval < 0)
                {
                    PRINT_ERROR("error forming 404 header (%d)\r\n", retval);
                    return -1;
                }
                return 0;
            }
            else
            { //time to execute cgi
                unsigned char cgiBuffer[HTTP_SERVER_CGI_BUFFER_SIZE];
                int retBufLength = http_CGI_exec_pathFunction(http_request.httpFilePath, (char *)&cgiBuffer, HTTP_SERVER_CGI_BUFFER_SIZE);
                if (retBufLength < 0)
                { //send an internal error response
                    PRINT_ERROR("error executing pathFunction (%s - %d)\r\n", http_request.httpFilePath, retBufLength);
                    int retval = http_server_send_serverError500(&httpResponse, socket, netops);
                    if (retval < 0)
                    {
                        PRINT_ERROR("error forming 500 header (%d)\r\n", retval);
                        return -1;
                    }
                    return 0;
                }
                else
                {
                    httpResponse.responseCode = HTTP_RESCODE_successSuccess; //200 OK
                    httpResponse.bodyLength = retBufLength;
                    httpResponse.filePath = NULL;
                    http_response_contenttype_t contentType = http_cgi_get_contentType(http_CGI_get_pathFunctionHandle(http_request.httpFilePath));
                    httpResponse.contentType = contentType;
                    retBufLen = http_response_response_header(httpResponse);
                    //check retval write and disconnect
                    if (retBufLen < 0)
                    {
                        PRINT_ERROR("error forming 200 header (%d)\r\n", retBufLen);
                        return -1;
                    }
                    netops->http_net_write(socket, (unsigned char *)httpHeaderBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS); //write header
                    if (retBufLen != 0)
                    { //case where operation was successful but no content to pass on.
                        netops->http_net_write(socket, (unsigned char *)cgiBuffer, retBufLength, HTTP_SERVER_TIMOUT_MS);
                    }
                    netops->http_net_disconnect(socket);
                    return 0;
                }
            }
        }
        break;
        default:
            //return server error
            break;
        }
        break;
    default: //currently supporting only GET. for all other requests, respond with not implemented.

        break;
    }
    return 0;
}
