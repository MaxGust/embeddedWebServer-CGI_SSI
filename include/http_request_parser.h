#ifndef __HTTP_REQUEST_PARSER_H__
#define __HTTP_REQUEST_PARSER_H__

#include "http_config.h"

//HTTP method enums
typedef enum {
    NONE = -1,
    GET = 1,
    POST,
    HEAD,
    PUT,
    DELETE,
    OPTIONS,
    CONNECT,
    TRACE,
    PATCH
} httpRequest_method_t; //enum to map HTTP request methods

//file type indicator
typedef enum {
    httpFileType_none = 0,
    httpFileType_SSI,
    httpFileType_CGI
} httpRequest_file_class_t; //enum to identify regular, SSI or CGI file types.

//parsed HTTP request
typedef struct
{
    httpRequest_file_class_t fileClass;            //contains the file type
    httpRequest_method_t method;             // contains teh requested method
    char httpFilePath[HTTP_MAX_PATH_LENGTH]; //contains file path
} http_request_t;                            //struct to hold results of parsing a HTTP request. Later header can be added here.

/*
parse and identify a request
*/
int parseRquest_identifyRequest(unsigned char *requestBuffer, http_request_t *httpRequest);

#endif
