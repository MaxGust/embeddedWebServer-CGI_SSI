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
*/

int http_server(int socket, http_net_netops_t *netops)
{
    unsigned char http_buffer[HTTP_SERVER_BUFFER_SIZE];
    int byteCount = netops->http_net_read(socket, (unsigned char *)&http_buffer, HTTP_SERVER_BUFFER_SIZE, HTTP_SERVER_TIMOUT_MS);
    if (byteCount <= 0)
    {
        return -1; //most probably a timeout error to read from client
    }

    //now the request headers are in buffer. time to parse teh request
    http_request_t http_request;
    parseRquest_identifyRequest(http_buffer, &http_request);

    switch (http_request.method)
    {
    case GET:
        switch (http_request.fileClass)
        {
        case httpFileType_none:
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