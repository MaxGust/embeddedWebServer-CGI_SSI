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

#ifndef __HTTP_CGI_H__
#define __HTTP_CGI_H__

#include "http_config.h"
#include "http_response.h" //for contentType

/*
callback to be registered for CGI path function along with a string. 
When a registered CGI path function is found in the page, the associated callback will be called to 
provide the dynamic replacement contents 

populate the buffer with required contents and returns actual buffer content length for success
     -1 for failure
     0 for no return content (Just a 200 OK will be sent to client)
*/

typedef int (*http_CGI_pathFunction_cb)(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);

/*The below structure holds the pointer to a static string to be replaced and 
  the corresponding replacer function that returns the replacement string. 
*/
typedef struct
{
    char *CGI_path;
    http_CGI_pathFunction_cb CGI_pathFunction;
    http_response_contenttype_t contentType;
} http_CGI_pathFunction_t;

typedef http_CGI_pathFunction_t *http_CGI_pathFunctionHandle_t;
/*function used to register a CGI pathFunction function. 
    IN : CGI path, associated callback function and contentType of function output
         contentType will be used to form response header
    OUT : 0  = Success
        : -1 = Failure
*/
http_CGI_pathFunctionHandle_t http_CGI_register_pathFunction(const char *CGIPath, http_CGI_pathFunction_cb CGIPathFunctionCb, http_response_contenttype_t contentType);

/*function to populate replacement buffer*/
int http_CGI_exec_pathFunction(char *CGIPath, char *replacerBuffer, unsigned int bufferLength);

/*function to de-register a specific replacement handle
incoming deregisterHandle will invalid NULL after this process.
*/
void http_CGI_deRegister_pathFunction(http_CGI_pathFunctionHandle_t deregisterHandle);

/*function to deregister all registrations in one go. Useful for shutdown*/
void http_CGI_deRegister_all(void);

/*debug function to print teh complete registration table*/
void http_CGI_printPathFunctionTable(void);

/*get return content type of a specified path function using its handle*/
http_response_contenttype_t http_cgi_get_contentType(http_CGI_pathFunctionHandle_t pathFunctionHandle);

//function to get pathFunction handle of a path
http_CGI_pathFunctionHandle_t http_CGI_get_pathFunctionHandle(char *CGIPath);
#endif