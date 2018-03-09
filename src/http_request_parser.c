/*
   Function to parse incoming request buffer and identify the request method,
   and path. 

   At this initial stage , query strings and headers will not be handled since
   the initial version is targeting just GET requests. 
*/

#include "http_request_parser.h"
#include "helperFunctions.h"
#include "http_config.h"
#include "http_common.h"
#include <string.h>
#include <stdio.h>

//list of file types supporting SSI
unsigned int httpFileType_SSIList_size = 4;
const char *const httpFileType_SSIList[] = {"shtml", "shtm", "ssi", "xml"};
//list of file types supporting CGI
unsigned int httpFileType_CGIList_size = 3;
const char *const httpFileType_CGIList[] = {"cgi", "sh", "exe"};

static httpRequest_method_t parseRequest_mapMethodToEnum(char *method)
{
    /*since most requesters send method in caps, toUpper is not applied */
    if (0 == strcmp(method, "GET"))
        return GET;
    else if (0 == strcmp(method, "POST"))
        return POST;
    else if (0 == strcmp(method, "PUT"))
        return PUT;
    else if (0 == strcmp(method, "HEAD"))
        return HEAD;
    else if (0 == strcmp(method, "DELETE"))
        return DELETE;
    else if (0 == strcmp(method, "OPTIONS"))
        return OPTIONS;
    else if (0 == strcmp(method, "CONNECT"))
        return CONNECT;
    else if (0 == strcmp(method, "TRACE"))
        return TRACE;
    else if (0 == strcmp(method, "PATCH"))
        return PATCH;
    else
        return NONE;
}

//identify whether the requested file is CGI/SSI or just for regular contents.
static httpFileType_code_t parseRequest_identifyFileClass(char *path)
{
    char *fileType = strrchr(path, '.'); //can hit some real corner case where there is no extension and thre is a . in path
    if (0 == fileType)
    {
        return httpFileType_none;
    }
    else
    {
        fileType += 1; //to remove the .
    }

    int i = 0;
    for (i = 0; i < httpFileType_SSIList_size; i++)
    {
        if (0 == strcmp(httpFileType_SSIList[i], fileType))
            return httpFileType_SSI;
    }

    for (i = 0; i < httpFileType_CGIList_size; i++)
    {
        if (0 == strcmp(httpFileType_CGIList[i], fileType))
            return httpFileType_CGI;
    }

    return httpFileType_none;
}
int parseRquest_identifyRequest(char *requestBuffer, http_request_t *httpRequest)
{

    const char *startOfPath = strchr(requestBuffer, ' ') + 1;
    const char *endOfPath;

    if (strstr(requestBuffer, "?"))
    { //if there is a query string, path ends at the start of query
        endOfPath = strchr(startOfPath, '?');
    }
    else if (strstr(requestBuffer, "HTTP/1."))
    { //if there is a HTTP version mentioned, path ends there
        endOfPath = strchr(startOfPath, ' ');
    }
    else
    {
        endOfPath = strchr(startOfPath, '\n'); //if none of the above, path ends at newline
    }
    //getting enough memory
    //TODO: will this work in embedded?
    char *methordToken = strtok(requestBuffer, " ");
    char method[strlen(methordToken) + 1];
    char path[endOfPath - startOfPath];

    //copying internally
    strncpy(method, methordToken, strlen(methordToken));
    strncpy(path, startOfPath, endOfPath - startOfPath);

    //null termination
    method[sizeof(method)] = 0; //-1 to remove trailing space
    path[sizeof(path) - 1] = 0; //-1 to remove trailing space

    //parse and copy method for returning.
    httpRequest->method = parseRequest_mapMethodToEnum(method);

    //decode URL and copy path for returning.
    char decodedURL[sizeof(path)];
    url_decode(path, decodedURL);
    strncpy(httpRequest->httpFilePath, decodedURL, HTTP_MAX_PATH_LENGTH);

    //decode file type and add copy it for returning
    httpRequest->fileType = parseRequest_identifyFileClass(path);

    //return success
    return HTTP_SUCCESS;
}
