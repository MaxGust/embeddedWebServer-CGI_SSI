/**MIT License

Copyright (c) 2018 Vysakh P Pillai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

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
    httpFileClass_none = 0,
    httpFileClass_SSI,
    httpFileClass_CGI
} httpRequest_fileClass_t; //enum to identify regular, SSI or CGI file types.

//parsed HTTP request
typedef struct
{
    httpRequest_fileClass_t fileClass;            //contains the file type
    httpRequest_method_t method;             // contains teh requested method
    char httpFilePath[HTTP_MAX_PATH_LENGTH]; //contains file path
} http_request_t;                            //struct to hold results of parsing a HTTP request. Later header can be added here.

/*
parse and identify a request
*/
int parseRquest_identifyRequest(unsigned char *requestBuffer, http_request_t *httpRequest);

#endif
