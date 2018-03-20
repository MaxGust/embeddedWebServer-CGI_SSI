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