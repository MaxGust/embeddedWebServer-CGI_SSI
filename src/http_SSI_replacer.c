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


#include <string.h>
#include <stdlib.h>
#include "http_SSI_replacer.h"
#include "http_config.h"
#include "http_common.h"

/*defining this as array for the following reasons
1) lookup speed is better than linked list
2) configuration is static and fixed at compile time. This can be adjusted in http_config.h 
*/
http_SSI_replacer_t http_SSI_replacer[HTTP_MAX_SSI_COUNT]; //hoping compiler to do its job and init to 0

int http_SSI_get_replacer_string(char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
    int i;
    for (i = 0; i < HTTP_MAX_SSI_COUNT; i++)
    { //find an empty slot and fill in the registration
        if (NULL != http_SSI_replacer[i].SSI_String)
        {
            if (0 == strcmp(SSIString, http_SSI_replacer[i].SSI_String))
            {
                return http_SSI_replacer[i].SSI_stringReplacer(SSIString, replacerBuffer, bufferLength);
            }
        }
    }
    return -1;
}

http_SSI_replacerHandle_t http_SSI_register_replacer(const char *SSIString, http_SSI_replacer_cb SSIReplacerCb)
{
    //find a uninitialized array element
    if ((NULL == SSIString) || (NULL == SSIReplacerCb))
    {
        PRINT_ERROR("NULL SSIString or CB (%p) \r\n", (void *)SSIString);
        return 0;
    }
    else
    {
        int i = 0;
        for (i = 0; i < HTTP_MAX_SSI_COUNT; i++)
        { //find an empty slot and fill in the registration
            if (NULL == http_SSI_replacer[i].SSI_String)
            {
                //allocate memory and copy string to it.
                http_SSI_replacer[i].SSI_String = (char *)malloc((size_t)strlen(SSIString) + 1);
                strncpy(http_SSI_replacer[i].SSI_String, SSIString, strlen(SSIString));
                http_SSI_replacer[i].SSI_String[strlen(SSIString)] = 0;

                http_SSI_replacer[i].SSI_stringReplacer = SSIReplacerCb;
                return &http_SSI_replacer[i];
            }
        }
        PRINT_ERROR("no more slots to register(%d)\r\n", i);
        return NULL;
    }
    return NULL; //Just a safety net.
}

void http_SSI_deRegister_replacer(http_SSI_replacerHandle_t deregisterHandle)
{
    //free the strings?
    //make contents in array 0
    free(deregisterHandle->SSI_String);
    deregisterHandle->SSI_String = NULL;
    deregisterHandle->SSI_stringReplacer = NULL;
    deregisterHandle = NULL;
}

//deregister all registrations in one-go. Useful to implement a shutdown function
void http_SSI_deRegister_all(void)
{
    int i = 0;
    for (i = 0; i < HTTP_MAX_SSI_COUNT; i++)
    { //find an empty slot and fill in the registration
        if (0 != http_SSI_replacer[i].SSI_String)
        {
            //free the string memory from heap
            free(http_SSI_replacer[i].SSI_String);
            http_SSI_replacer[i].SSI_String = NULL;
            http_SSI_replacer[i].SSI_stringReplacer = NULL;
        }
    }
}

//temporarily commented off to fix pedantic errors. Not major since this is this is a test function. Issue #2
#ifdef HTTP_REPLACER_TABLE_DEBUG_PRINTF
//test function to print complete registration table. to be used only for debugging
void http_SSI_printReplacerTable(void)
{
    int i;
    printf("REPLACER\t\tSTRING\r\n");
    for (i = 0; i < HTTP_MAX_SSI_COUNT; i++)
    {
        printf("%p\t\t", (void *)http_SSI_replacer[i].SSI_stringReplacer);
        printf("%s\r\n", http_SSI_replacer[i].SSI_String);
    }
    printf("==============================================================\r\n");
}
#endif