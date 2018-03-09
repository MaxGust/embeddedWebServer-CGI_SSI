#include <string.h>
#include "http_SSI_functionRegistration.h"
#include "http_config.h"
#include "http_common.h"

http_SSI_replacer_t http_SSI_replacer[HTTP_MAX_SSI_SIZE];
static int http_SSI_replacerIndex;  //store current number of registrations

http_SSI_replacerHandle_t http_SSI_register_replacer(const char *SSIString, http_SSI_replacer_cb SSIReplacerCb)
{

}

int http_SSI_deRegister_replacer(http_SSI_replacerHandle_t deregisterHandle)
{
    //free the stuff?
    //make contents in array 0
}