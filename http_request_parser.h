#ifndef __HTTP_REQUEST_PARSER_H__
#define __HTTP_REQUEST_PARSER_H__

#define HTTP_MAX_PATH_LENGTH 100
#define HTTP_MAX_METHOD_LENGTH 8


//HTTP method enums
typedef enum {
    NONE=-1,
    GET=1,
    POST,
    HEAD,
    PUT,
    DELETE,
    OPTIONS,
    CONNECT,
    TRACE,
    PATCH
}httpRequest_method_t;


//file type indicator 
typedef enum {
  httpFileType_none=0,
  httpFileType_SSI,
  httpFileType_CGI
}httpFileType_code_t;

//parsed HTTP request
typedef struct {
  httpFileType_code_t fileType;        //contains the file type
  httpRequest_method_t method;          // contains teh requested method
  char httpFilePath[HTTP_MAX_PATH_LENGTH]; //contains file path
}http_request_t;



/*
parse and identify a request
*/
int parseRquest_identifyRequest(char* requestBuffer,http_request_t* httpRequest);

#endif