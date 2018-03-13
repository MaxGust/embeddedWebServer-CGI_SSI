#include "http_config.h"
#include "http_common.h"
#include "http_file.h"
#include "http_net.h"
#include "http_request_parser.h"
#include "http_SSI_replacer.h"
#include "http_response.h"
#include "http_server.h"

/*this connection is a per-connection server
    precondition: 
        - netops and fops should have been registered
        - file system should be mounted and files should be registered
*/

int http_server(int socket, http_net_netops_t *netops)
{
    unsigned char httpReadBuffer[HTTP_SERVER_READ_BUFFER_SIZE];
    char httpWriteBuffer[HTTP_SERVER_WRITE_BUFFER_SIZE];
    if ((NULL == netops->http_net_read)||(NULL == netops->http_net_write))
    {
        PRINT_ERROR("netops read not initialized(%d)\r\n", (int)netops);
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
    void* fp;
    int retval=0;
    HTTP_response_headerRequest_t httpResponse;
    http_response_initReponseStruct(&httpResponse);
    httpResponse.headerBuffer=(char*)&httpWriteBuffer;
    httpResponse.bufferLength=HTTP_SERVER_WRITE_BUFFER_SIZE;

    switch (http_request.method)
    {
    case GET:
        switch (http_request.fileClass)
        {
        case httpFileType_none: //regular File processing flow
                fp=http_file_fops.fopen(http_request.httpFilePath);
                if(NULL==fp){//file not found
                    httpResponse.responseCode=HTTP_RESCODE_cerrorNotfound;
                    retval=http_response_response_header(httpResponse);
                    //check retval write and disconnect
                }
            break;
        case httpFileType_SSI:
            break;
        case httpFileType_CGI:
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