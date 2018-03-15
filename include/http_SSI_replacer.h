#ifndef __HTTP_SSI_REPLACER_H__
#define __HTTP_SSI_REPLACER_H__

#include "http_config.h"

/*
callback to be registered for SSI replacement along with a string. 
When a registered SSI string is found in the page, the associated callback will be called to 
provide the dynamic replacement contents 

populate the buffer with required contents and return 0 for success;
*/

typedef int (*http_SSI_replacer_cb)(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);

/*The below structure holds the pointer to a static string to be replaced and 
  the corresponding replacer function that returns the replacement string. 
*/
typedef struct
{
    char *SSI_String;
    http_SSI_replacer_cb SSI_stringReplacer;
} http_SSI_replacer_t;

typedef http_SSI_replacer_t *http_SSI_replacerHandle_t;

extern http_SSI_replacer_t http_SSI_replacer[];

/*function used to register a SSI string replacer function. 
    IN : "static" string to be replaced and associated callback function
    OUT : 0  = Success
        : -1 = Failure
*/
http_SSI_replacerHandle_t http_SSI_register_replacer(const char *SSIString, http_SSI_replacer_cb SSIReplacerCb);

/*function to populate replacement buffer*/
int http_SSI_get_replacer_string(char *SSIString, char *replacerBuffer, unsigned int bufferLength);

/*function to de-register a specific replacement handle
incoming deregisterHandle will invalid NULL after this process.
*/
void http_SSI_deRegister_replacer(http_SSI_replacerHandle_t deregisterHandle);

/*function to deregister all registrations in one go. Useful for shutdown*/
void http_SSI_deRegister_all(void);

/*debug function to print teh complete registration table*/
void http_SSI_printReplacerTable(void);

#endif