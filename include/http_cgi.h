#ifndef __HTTP_CGI_H__
#define __HTTP_CGI_H__

#include "http_config.h"

/*
callback to be registered for CGI path function along with a string. 
When a registered CGI path function is found in the page, the associated callback will be called to 
provide the dynamic replacement contents 

populate the buffer with required contents and return 0 for success;
*/

typedef int (*http_CGI_pathFunction_cb)(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);

/*The below structure holds the pointer to a static string to be replaced and 
  the corresponding replacer function that returns the replacement string. 
*/
typedef struct
{
    char *CGI_path;
    http_CGI_pathFunction_cb CGI_pathFunction;
} http_CGI_pathFunction_t;

typedef http_CGI_pathFunction_t *http_CGI_pathFunctionHandle_t;
/*function used to register a CGI pathFunction function. 
    IN : "static" string to be replaced and associated callback function
    OUT : 0  = Success
        : -1 = Failure
*/
http_CGI_pathFunctionHandle_t http_CGI_register_pathFunction(const char *CGIPath, http_CGI_pathFunction_cb CGIPathFunctionCb);

/*function to populate replacement buffer*/
int http_CGI_exec_pathFunction(char *CGIPath, char *replacerBuffer, unsigned int bufferLength);

/*function to de-register a specific replacement handle
incoming deregisterHandle will invalid NULL after this process.
*/
void http_CGI_deRegister_pathFunction(http_CGI_pathFunctionHandle_t deregisterHandle);

/*function to deregister all registrations in one go. Useful for shutdown*/
void http_CGI_deRegister_all();

/*debug function to print teh complete registration table*/
void http_CGI_printPathFunctionTable();

#endif