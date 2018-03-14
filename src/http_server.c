#include "http_config.h"
#include "http_common.h"
#include "http_file.h"
#include "http_net.h"
#include "http_request_parser.h"
#include "http_SSI_replacer.h"
#include "http_response.h"
#include "http_server.h"
#include "http_cgi.h"

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

int http_server(int socket, http_net_netops_t *netops)
{
    unsigned char httpReadBuffer[HTTP_SERVER_READ_BUFFER_SIZE];
    char httpHeaderBuffer[HTTP_SERVER_HEADER_BUFFER_SIZE];
    if ((NULL == netops->http_net_read) || (NULL == netops->http_net_write))
    {
        PRINT_ERROR("netops read not initialized(%s)\r\n", "nullNetops");
        return -1;
    }
    int byteCount = netops->http_net_read(socket, (unsigned char *)&httpReadBuffer, HTTP_SERVER_READ_BUFFER_SIZE, HTTP_SERVER_TIMOUT_MS);
    if (byteCount <= 0)
    {
        PRINT_ERROR("netops read timedout(%d)\r\n", byteCount);
        return -1; //most probably a timeout error to read from client
    }

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
        case httpFileType_none: //regular File processing flow
            if (NULL != http_file_fops.fopen)
            { //else FS is not mounted
                fp = http_file_fops.fopen(http_request.httpFilePath);
            }
            else
            {
                PRINT_ERROR("fops not mounted(%d)\r\n", httpFileType_none);
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
                if (http_file_fops.feof(fp))
                {                                                            //complete contents has been read to buffer. no chunking required
                    httpResponse.responseCode = HTTP_RESCODE_successSuccess; //200 OK
                    httpResponse.bodyLength = readLen;
                    httpResponse.filePath = http_request.httpFilePath;
                    retBufLen = http_response_response_header(httpResponse);
                    //check retval write and disconnect
                    if (retBufLen <= 0)
                    {
                        PRINT_ERROR("error forming 404 header (%d)\r\n", httpFileType_none);
                        return -1;
                    }
                    netops->http_net_write(socket, (unsigned char *)httpHeaderBuffer, retBufLen, HTTP_SERVER_TIMOUT_MS); //write header
                    netops->http_net_write(socket, (unsigned char *)freadBuffer, readLen, HTTP_SERVER_TIMOUT_MS);        //
                    netops->http_net_disconnect(socket);
                    return 0;
                }
                else
                { //time to do chunked encoding
                }
            }
            break;
        case httpFileType_SSI:
            break;
        case httpFileType_CGI:
        {
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
            else{//time to execute cgi
                
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