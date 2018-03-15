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
