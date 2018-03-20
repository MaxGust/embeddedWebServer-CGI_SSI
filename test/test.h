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

#ifndef __HTTP_TEST_H__
#define __HTTP_TEST_H__

#include <stdio.h>
#include <string.h>
#include "helperFunctions.h"
#include "http_request_parser.h"
#include "http_common.h"
#include "http_config.h"
#include "http_SSI_replacer.h"
#include "http_cgi.h"
#include "http_response.h"
#include "http_local_filesystem.h"
#include "http_file.h"
#include "http_net.h"
#include "http_server.h"


#define PASS "\x1B[1;32mPASS:\x1B[0m\t"
#define FAIL "\x1B[1;31mFAIL:\x1B[0m\t"


/*test routine to check if method type , file path and file type are parsed properly*/
int test_methodFileType(void);
int timerVal_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);
int sysStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);
int resetStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength);
int test_SSIStringRegistration(void);
int test_SSIStringReplacementCB(void);
int exec1_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);
int exec2_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);
int exec3_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);
int test_CGI_registration(void);
int test_CGI_exec(void);
int test_response_fileType(void);
int test_response_contentType(void);
int test_response_header(void);
int test_file_local_filesystem(void);
int test_http_file(void);
int test_http_net(void);
int test_http_server(void);



#endif
