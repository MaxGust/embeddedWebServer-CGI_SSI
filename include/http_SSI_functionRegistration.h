#ifndef __HTTP_SSI_FUNCTION_RAGISTRATION_H__
#define __HTTP_SSI_FUNCTION_RAGISTRATION_H__

#include "http_config.h"

/*callback to be registered for SSI replacement along with a string. 
When a registered SSI string is found in the page, the associated callback will be called to 
provide the dynamic replacement contents */

typedef char *(*http_SSI_replacer_cb)(const char *SSIString);

/*The below structure holds the pointer to a static string to be replaced and 
  the corresponding replacer function that returns the replacement string. 
*/
typedef struct{
    const char* SSI_String;
    http_SSI_replacer_cb SSI_stringReplacer;
    unsigned int SSI_replacer_arrayIndex;
}http_SSI_replacer_t;

typedef http_SSI_replacer_t* http_SSI_replacerHandle_t
/*function used to register a SSI string replacer function. 
    IN : string to be replaced and associated callback function
    OUT : 0  = Success
        : -1 = Failure
*/
http_SSI_replacerHandle_t http_SSI_register_replacer(const char *SSIString, http_SSI_replacer_cb SSIReplacerCb);

/*function to deRegister a SSI replacement function*/
int http_SSI_deRegister_replacer(http_SSI_replacerHandle_t deregisterHandle);

#endif