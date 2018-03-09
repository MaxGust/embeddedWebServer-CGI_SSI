#ifndef __HTTP_SSI_FUNCTION_RAGISTRATION_H__
#define __HTTP_SSI_FUNCTION_RAGISTRATION_H__

#include "http_config.h"

/*callback to be registered for SSI replacement along with a string. 
When a registered SSI string is found in the page, the associated callback will be called to 
provide the dynamic replacement contents */

typedef char* (*http_SSI_replacer_cb) (const char *SSIString);

/*function used to register a SSI string replacer function. 
    IN : string to be replaced and associated callback function
    OUT : 0  = Success
        : -1 = Failure
*/
int http_SSI_registerReplacer(const char* SSIString,http_SSI_replacer_cb SSIReplacerCb);

#endif