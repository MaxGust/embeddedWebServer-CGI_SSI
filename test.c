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

int test_methodFileType(void)
{
  unsigned char requestBuffer[] = "GET /ta.gs/ref_htt%20%20pmethods.shtm\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  int retVal = 0;
  http_request_t request;
  //printf("%s\r\n", requestBuffer);
  retVal = parseRquest_identifyRequest(requestBuffer, &request);
  if (HTTP_SUCCESS == retVal)
  {
    if ((httpFileClass_SSI == request.fileClass) && (GET == request.method) && (0 == strcmp(request.httpFilePath, "/ta.gs/ref_htt  pmethods.shtm")))
    {
      printf(PASS "test_methodFileType (SSI GET)\r\n");
      return 0;
    }
    else
    {
      //printf("result\r\n\tfileType: %d\r\n\tmethod: %d\r\n\tpath:%s\r\n\r\n", request.fileType, request.method, request.httpFilePath);
      printf(FAIL "test_methodFileType(SSI GET)\r\n");
      return -1;
    }
  }
  else
  {
    //printf("result\r\n\tfileType: %d\r\n\tmethod: %d\r\n\tpath:%s\r\n\r\n", request.fileType, request.method, request.httpFilePath);
    printf(FAIL "test_methodFileType(2)\r\n");
    return -1;
  }
  return -1;
}

/*test callbacks to replace SSI string timerVal*/
int timerVal_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("timerVal", SSIString))
  {
    printf(FAIL "timerVal_SSI_replacer_cb (SSI string missmatch)\r\n");
    return -1;
  }
  strncpy(replacerBuffer, "timerValue is 200", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int sysStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("sysStatus", SSIString))
  {
    printf(FAIL "sysStatus_SSI_replacer_cb (SSI string missmatch)\r\n");
    return -1;
  }
  strncpy(replacerBuffer, "System is up and running", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int resetStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("resetStatus", SSIString))
  {
    printf(FAIL "resetStatus_SSI_replacer_cb (SSI string missmatch)\r\n");
    return -1;
  }
  strncpy(replacerBuffer, "Previous reset caused by Watchdog", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}

/*test routine to check if callback registration for SSI string is done properly*/
int test_SSIStringRegistration(void)
{
  char *testSSIString1 = "timerVal";
  char *testSSIString2 = "sysStatus";
  char *testSSIString3 = "resetStatus";

  http_SSI_replacer_t *SSIReplacementHandle1;
  SSIReplacementHandle1 = http_SSI_register_replacer(testSSIString1, timerVal_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle1)
  {
    printf(FAIL "test_SSIStringRegistration(http_SSI_register_replacer 1)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(http_SSI_register_replacer 1)\r\n");

#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  http_SSI_replacer_t *SSIReplacementHandle2;
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString2, sysStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf(FAIL "test_SSIStringRegistration(2)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(http_SSI_register_replacer 2)\r\n");
#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  http_SSI_replacer_t *SSIReplacementHandle3;
  SSIReplacementHandle3 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle3)
  {
    printf(FAIL "test_SSIStringRegistration(3)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(http_SSI_register_replacer 3)\r\n");

#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  http_SSI_deRegister_replacer(SSIReplacementHandle2);
#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  //multiple registrations of the same CB
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf(FAIL "test_SSIStringRegistration(4)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(register after deregister)\r\n");

#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  printf(PASS ">>test_SSIStringRegistration<<\r\n");
  return 0;
}

/*unittest for replacement matching */
int test_SSIStringReplacementCB(void)
{
  char stringArray[100];
  //try for replacement string of "timerVal"
  if (0 == http_SSI_get_replacer_string("timerVal", (char *)&stringArray, sizeof(stringArray)))
  {
    if (0 != strcmp(stringArray, "timerValue is 200"))
    {
      printf(FAIL "test_SSIStringReplacementCB(1)\r\n");
      return -1;
    }
  }

  //try for a non-existant SSI string
  if (0 == http_SSI_get_replacer_string("nonExistantVal", (char *)&stringArray, sizeof(stringArray)))
  {
    printf(FAIL "test_SSIStringReplacementCB(2)\r\n");
    return -1;
  }

  //deregister all replacers
  http_SSI_deRegister_all();

  printf(PASS "test_SSIStringReplacementCB\r\n");
  return 0;
}

/*test callbacks to replace SSI string timerVal*/
int exec1_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("/CGI/exec1.cgi", CGIPath))
  {
    return -1;
  }
  strncpy(replacerBuffer, "exec1 Executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return (int)strlen("exec1 Executed");
}
int exec2_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("/bin/exec2.sh", CGIPath))
  {
    return -1;
  }
  strncpy(replacerBuffer, "exec2 Executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return (int)strlen("exec2 Executed");
}
int exec3_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("/exec3.exe", CGIPath))
  {
    return -1;
  }
  strncpy(replacerBuffer, "exec3 executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return (int)strlen("exec3 Executed");
}

/*unit test for CGI*/
int test_CGI_registration(void)
{
  char *cgiPath1 = "/CGI/exec1.cgi";
  char *cgiPath2 = "/bin/exec2.sh";
  char *cgiPath3 = "/exec3.exe";

  http_CGI_pathFunction_t *cgiPathHandle1;
  cgiPathHandle1 = http_CGI_register_pathFunction(cgiPath1, exec1_CGI_cb, HTTP_contentType_bin);
  if (NULL == cgiPathHandle1)
  {
    printf(FAIL "test_CGI(1)\r\n");
    return -1;
  }
  if (HTTP_contentType_bin != http_cgi_get_contentType(cgiPathHandle1))
  {
    printf(FAIL "test_CGI(cgiPathHandle1 content type)\r\n");
    return -1;
  }

#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  http_CGI_pathFunction_t *cgiPathHandle2;
  cgiPathHandle2 = http_CGI_register_pathFunction(cgiPath2, exec2_CGI_cb, HTTP_contentType_bin);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_CGI(2)");
    return -1;
  }
  if (HTTP_contentType_bin != http_cgi_get_contentType(cgiPathHandle2))
  {
    printf(FAIL "test_CGI(cgiPathHandle2 content type)\r\n");
    return -1;
  }

#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  http_CGI_pathFunction_t *cgiPathHandle3;
  cgiPathHandle3 = http_CGI_register_pathFunction(cgiPath3, exec3_CGI_cb, HTTP_contentType_json);
  if (NULL == cgiPathHandle3)
  {
    printf(FAIL "test_CGI(3)");
    return -1;
  }
  if (HTTP_contentType_json != http_cgi_get_contentType(cgiPathHandle3))
  {
    printf(FAIL "test_CGI(cgiPathHandle3 content type)\r\n");
    return -1;
  }
#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  http_CGI_deRegister_pathFunction(cgiPathHandle2);
#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  //multiple registrations of the same CB
  cgiPathHandle2 = http_CGI_register_pathFunction(cgiPath3, exec3_CGI_cb, HTTP_contentType_plaintext);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_CGI(4)");
    return -1;
  }
  if (HTTP_contentType_plaintext != http_cgi_get_contentType(cgiPathHandle2))
  {
    printf(FAIL "test_CGI(cgiPathHandle2 [rereg] content type)\r\n");
    return -1;
  }
#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  printf(PASS "test_CGI\r\n");
  return 0;
}

int test_CGI_exec(void)
{
  char stringArray[100];
  //try for exec of "/CGI/exec1.cgi"
  if (strlen("exec1 Executed") == http_CGI_exec_pathFunction("/CGI/exec1.cgi", (char *)&stringArray, sizeof(stringArray)))
  {
    if (0 != strcmp(stringArray, "exec1 Executed"))
    {
      printf(FAIL "test_CGI_exec(1)\r\n");
      return -1;
    }
  }

  //try for a non-existant SSI string
  if (http_CGI_exec_pathFunction("nonExistantVal", (char *)&stringArray, sizeof(stringArray)) >= 0)
  {
    printf(FAIL "test_CGI_exec(2)\r\n");
    return -1;
  }

  //deregister all replacers
  http_CGI_deRegister_all();

  printf(PASS "test_CGI_exec\r\n");
  return 0;
}

int test_response_fileType(void)
{
  char *testPath1 = "/index.html";
  char *testPath2 = "/index.shtml";
  char *testPath3 = "/index.txt";
  char *testPath4 = "/index.shtm";
  char *testPath5 = "/index.ssi";
  char *testPath6 = "/index.css";
  char *testPath7 = "/index.js";
  char *testPath8 = "/index.json";
  char *testPath9 = "/index.jpeg";
  char *testPath10 = "/index.png";
  char *testPath11 = "/index.bin";
  char *testPath12 = "/index.csv";
  char *testPath13 = "/index.gif";
  char *testPath14 = "/index.ico";
  char *testPath15 = "/index.zip";
  char *testPath16 = "/index";

  http_response_fileType_t fileType;
  fileType = http_response_getFileType(testPath1);
  if (HTTP_fileType_HTML != fileType)
  {
    printf(FAIL "test_response_fileType(1)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath2);
  if (HTTP_fileType_SHTML != fileType)
  {
    printf(FAIL "test_response_fileType(2)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath3);
  if (HTTP_fileType_TXT != fileType)
  {
    printf(FAIL "test_response_fileType(3)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath4);
  if (HTTP_fileType_SHTM != fileType)
  {
    printf(FAIL "test_response_fileType(4)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath5);
  if (HTTP_fileType_SSI != fileType)
  {
    printf(FAIL "test_response_fileType(5)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath6);
  if (HTTP_fileType_CSS != fileType)
  {
    printf(FAIL "test_response_fileType(6)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath7);
  if (HTTP_fileType_JS != fileType)
  {
    printf(FAIL "test_response_fileType(7)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath8);
  if (HTTP_fileType_JSON != fileType)
  {
    printf(FAIL "test_response_fileType(8)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath9);
  if (HTTP_fileType_JPEG != fileType)
  {
    printf(FAIL "test_response_fileType(9)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath10);
  if (HTTP_fileType_PNG != fileType)
  {
    printf(FAIL "test_response_fileType(10)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath11);
  if (HTTP_fileType_BIN != fileType)
  {
    printf(FAIL "test_response_fileType(11)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath12);
  if (HTTP_fileType_CSV != fileType)
  {
    printf(FAIL "test_response_fileType(12)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath13);
  if (HTTP_fileType_GIF != fileType)
  {
    printf(FAIL "test_response_fileType(13)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath14);
  if (HTTP_fileType_ICO != fileType)
  {
    printf(FAIL "test_response_fileType(14)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath15);
  if (HTTP_fileType_ZIP != fileType)
  {
    printf(FAIL "test_response_fileType(15)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath16);
  if (HTTP_fileType_unknown != fileType)
  {
    printf(FAIL "test_response_fileType(16)\r\n");
    return -1;
  }

  printf(PASS "test_response_fileType\r\n");
  return 0;
}

int test_response_contentType(void)
{
  http_response_contenttype_t contentType;
  char buffer[100];

  contentType = http_response_get_contentType_string(HTTP_fileType_HTML, (char *)&buffer, 100);
  if (HTTP_contentType_html != contentType)
  {
    printf(FAIL "test_response_contentType(1)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_HTML, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(2)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_TXT, (char *)&buffer, 100);
  if (HTTP_contentType_plaintext != contentType)
  {
    printf(FAIL "test_response_contentType(3)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_PLAINTEXT, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(4)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_CSS, (char *)&buffer, 100);
  if (HTTP_contentType_css != contentType)
  {
    printf(FAIL "test_response_contentType(5)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_CSS, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(6)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_JS, (char *)&buffer, 100);
  if (HTTP_contentType_js != contentType)
  {
    printf(FAIL "test_response_contentType(7)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_JS, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(8)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_JSON, (char *)&buffer, 100);
  if (HTTP_contentType_json != contentType)
  {
    printf(FAIL "test_response_contentType(9)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_JSON, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(10)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_JPEG, (char *)&buffer, 100);
  if (HTTP_contentType_jpeg != contentType)
  {
    printf(FAIL "test_response_contentType(11)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_JPEG, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(12)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_PNG, (char *)&buffer, 100);
  if (HTTP_contentType_png != contentType)
  {
    printf(FAIL "test_response_contentType(13)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_PNG, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(14)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_BIN, (char *)&buffer, 100);
  if (HTTP_contentType_bin != contentType)
  {
    printf(FAIL "test_response_contentType(15)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_BIN, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(16)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_CSV, (char *)&buffer, 100);
  if (HTTP_contentType_csv != contentType)
  {
    printf(FAIL "test_response_contentType(17)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_CSV, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(18)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_GIF, (char *)&buffer, 100);
  if (HTTP_contentType_gif != contentType)
  {
    printf(FAIL "test_response_contentType(19)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_GIF, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(20)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_ICO, (char *)&buffer, 100);
  if (HTTP_contentType_ico != contentType)
  {
    printf(FAIL "test_response_contentType(21)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_ICO, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(22)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_ZIP, (char *)&buffer, 100);
  if (HTTP_contentType_zip != contentType)
  {
    printf(FAIL "test_response_contentType(23)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_ZIP, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(24)\r\n");
    return -2;
  }

  printf(PASS "test_response_contentType\r\n");
  return 0;
}

int test_response_header(void)
{

  HTTP_response_headerRequest_t headerRequest;
  char headerBuffer[300];
  http_response_initReponseStruct(&headerRequest);
  headerRequest.responseCode = HTTP_RESCODE_successSuccess;
  headerRequest.bodyLength = 1024;
  headerRequest.headerBuffer = (char *)&headerBuffer;
  headerRequest.bufferLength = 300;
  headerRequest.transferEncoding = transferEnc_none;
  headerRequest.filePath = "/index.html";
  

  int retBufLen = 0;

  retBufLen = http_response_response_header(headerRequest);

  char *expectedResponse1 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 1024\r\n\r\n";

  if (strlen(expectedResponse1) != (unsigned int)retBufLen)
  {
    printf(FAIL "test_response_header(response length missmatch (200 OK))\r\n");
    return -1;
  }

  if (0 != strcmp(headerBuffer, expectedResponse1))
  {
    printf("%s\r\n", headerBuffer);
    printf(FAIL "test_response_header(1)\r\n");
    return -1;
  }

  headerRequest.filePath = NULL;
  headerRequest.responseCode = HTTP_RESCODE_serrorInternalerror; //invalid with content. just for unit test
  headerRequest.contentType = HTTP_contentType_bin;
  retBufLen = http_response_response_header(headerRequest);
  char *expectedResponse2 = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/octet-stream\r\nContent-Length: 1024\r\n\r\n";
  if (strlen(expectedResponse2) != (unsigned int)retBufLen)
  {
    printf(FAIL "test_response_header(response length HTTP_RESCODE_cerrorNotfound (500 Internal Error))\r\n");
    return -1;
  }
  if (0 != strcmp(headerBuffer, expectedResponse2))
  {
    printf(FAIL "test_response_header(2)\r\n");
    return -1;
  }

  //test chunked encoding with a different response code
  headerRequest.transferEncoding = transferEnc_chunked;
  headerRequest.responseCode = HTTP_RESCODE_cerrorNotfound;
  retBufLen = http_response_response_header(headerRequest);
  char *expectedResponse3 = "HTTP/1.1 404 Not Found\r\nContent-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n\r\n";

  if (strlen(expectedResponse3) != (unsigned int)retBufLen)
  {
    printf(FAIL "test_response_header(response length HTTP_RESCODE_cerrorNotfound)\r\n");
    return -1;
  }

  if (0 != strcmp(headerBuffer, expectedResponse3))
  {
    printf(FAIL "test_response_header(HTTP_RESCODE_cerrorNotfound)\r\n");
    return -1;
  }

  //test small input buffer
  headerRequest.bufferLength = 3;
  int retval = http_response_response_header(headerRequest);
  if (retval >= 0)
  {
    printf(FAIL "test_response_header(Short Buffer)\r\n");
    return -1;
  }

  // printf("\r\n%s",headerBuffer);
  printf(PASS "test_response_header\r\n");
  return 0;
}

//copy of index contents in new file for test
static unsigned char index1_html[] = {
    0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x62, 0x6f,
    0x64, 0x79, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x31, 0x3e,
    0x48, 0x45, 0x4c, 0x4c, 0x4f, 0x20, 0x57, 0x4f, 0x52, 0x4c, 0x44, 0x3c,
    0x2f, 0x48, 0x31, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x62, 0x6f, 0x64,
    0x79, 0x3e, 0x0a, 0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a};
static unsigned int index1_html_len = 59;
static char *path_index1_html = "/index1.html";

unsigned char index_long_html[] = {
  0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x62, 0x6f,
  0x64, 0x79, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x31, 0x3e,
  0x48, 0x45, 0x4c, 0x4c, 0x4f, 0x20, 0x57, 0x4f, 0x52, 0x4c, 0x44, 0x3c,
  0x2f, 0x48, 0x31, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x22, 0x4c, 0x6f,
  0x72, 0x65, 0x6d, 0x20, 0x69, 0x70, 0x73, 0x75, 0x6d, 0x20, 0x64, 0x6f,
  0x6c, 0x6f, 0x72, 0x20, 0x73, 0x69, 0x74, 0x20, 0x61, 0x6d, 0x65, 0x74,
  0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x65, 0x63, 0x74, 0x65, 0x74, 0x75,
  0x72, 0x20, 0x61, 0x64, 0x69, 0x70, 0x69, 0x73, 0x63, 0x69, 0x6e, 0x67,
  0x20, 0x65, 0x6c, 0x69, 0x74, 0x2c, 0x20, 0x73, 0x65, 0x64, 0x20, 0x64,
  0x6f, 0x20, 0x65, 0x69, 0x75, 0x73, 0x6d, 0x6f, 0x64, 0x20, 0x74, 0x65,
  0x6d, 0x70, 0x6f, 0x72, 0x20, 0x69, 0x6e, 0x63, 0x69, 0x64, 0x69, 0x64,
  0x75, 0x6e, 0x74, 0x20, 0x75, 0x74, 0x20, 0x6c, 0x61, 0x62, 0x6f, 0x72,
  0x65, 0x20, 0x65, 0x74, 0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x65, 0x20,
  0x6d, 0x61, 0x67, 0x6e, 0x61, 0x20, 0x61, 0x6c, 0x69, 0x71, 0x75, 0x61,
  0x2e, 0x20, 0x55, 0x74, 0x20, 0x65, 0x6e, 0x69, 0x6d, 0x20, 0x61, 0x64,
  0x20, 0x6d, 0x69, 0x6e, 0x69, 0x6d, 0x20, 0x76, 0x65, 0x6e, 0x69, 0x61,
  0x6d, 0x2c, 0x20, 0x71, 0x75, 0x69, 0x73, 0x20, 0x6e, 0x6f, 0x73, 0x74,
  0x72, 0x75, 0x64, 0x20, 0x65, 0x78, 0x65, 0x72, 0x63, 0x69, 0x74, 0x61,
  0x74, 0x69, 0x6f, 0x6e, 0x20, 0x75, 0x6c, 0x6c, 0x61, 0x6d, 0x63, 0x6f,
  0x20, 0x6c, 0x61, 0x62, 0x6f, 0x72, 0x69, 0x73, 0x20, 0x6e, 0x69, 0x73,
  0x69, 0x20, 0x75, 0x74, 0x20, 0x61, 0x6c, 0x69, 0x71, 0x75, 0x69, 0x70,
  0x20, 0x65, 0x78, 0x20, 0x65, 0x61, 0x20, 0x63, 0x6f, 0x6d, 0x6d, 0x6f,
  0x64, 0x6f, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x65, 0x71, 0x75, 0x61, 0x74,
  0x2e, 0x20, 0x44, 0x75, 0x69, 0x73, 0x20, 0x61, 0x75, 0x74, 0x65, 0x20,
  0x69, 0x72, 0x75, 0x72, 0x65, 0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x20,
  0x69, 0x6e, 0x20, 0x72, 0x65, 0x70, 0x72, 0x65, 0x68, 0x65, 0x6e, 0x64,
  0x65, 0x72, 0x69, 0x74, 0x20, 0x69, 0x6e, 0x20, 0x76, 0x6f, 0x6c, 0x75,
  0x70, 0x74, 0x61, 0x74, 0x65, 0x20, 0x76, 0x65, 0x6c, 0x69, 0x74, 0x20,
  0x65, 0x73, 0x73, 0x65, 0x20, 0x63, 0x69, 0x6c, 0x6c, 0x75, 0x6d, 0x20,
  0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x65, 0x20, 0x65, 0x75, 0x20, 0x66, 0x75,
  0x67, 0x69, 0x61, 0x74, 0x20, 0x6e, 0x75, 0x6c, 0x6c, 0x61, 0x20, 0x70,
  0x61, 0x72, 0x69, 0x61, 0x74, 0x75, 0x72, 0x2e, 0x20, 0x45, 0x78, 0x63,
  0x65, 0x70, 0x74, 0x65, 0x75, 0x72, 0x20, 0x73, 0x69, 0x6e, 0x74, 0x20,
  0x6f, 0x63, 0x63, 0x61, 0x65, 0x63, 0x61, 0x74, 0x20, 0x63, 0x75, 0x70,
  0x69, 0x64, 0x61, 0x74, 0x61, 0x74, 0x20, 0x6e, 0x6f, 0x6e, 0x20, 0x70,
  0x72, 0x6f, 0x69, 0x64, 0x65, 0x6e, 0x74, 0x2c, 0x20, 0x73, 0x75, 0x6e,
  0x74, 0x20, 0x69, 0x6e, 0x20, 0x63, 0x75, 0x6c, 0x70, 0x61, 0x20, 0x71,
  0x75, 0x69, 0x20, 0x6f, 0x66, 0x66, 0x69, 0x63, 0x69, 0x61, 0x20, 0x64,
  0x65, 0x73, 0x65, 0x72, 0x75, 0x6e, 0x74, 0x20, 0x6d, 0x6f, 0x6c, 0x6c,
  0x69, 0x74, 0x20, 0x61, 0x6e, 0x69, 0x6d, 0x20, 0x69, 0x64, 0x20, 0x65,
  0x73, 0x74, 0x20, 0x6c, 0x61, 0x62, 0x6f, 0x72, 0x75, 0x6d, 0x2e, 0x22,
  0x0a, 0x20, 0x20, 0x20, 0x20, 0x22, 0x4c, 0x6f, 0x72, 0x65, 0x6d, 0x20,
  0x69, 0x70, 0x73, 0x75, 0x6d, 0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x20,
  0x73, 0x69, 0x74, 0x20, 0x61, 0x6d, 0x65, 0x74, 0x2c, 0x20, 0x63, 0x6f,
  0x6e, 0x73, 0x65, 0x63, 0x74, 0x65, 0x74, 0x75, 0x72, 0x20, 0x61, 0x64,
  0x69, 0x70, 0x69, 0x73, 0x63, 0x69, 0x6e, 0x67, 0x20, 0x65, 0x6c, 0x69,
  0x74, 0x2c, 0x20, 0x73, 0x65, 0x64, 0x20, 0x64, 0x6f, 0x20, 0x65, 0x69,
  0x75, 0x73, 0x6d, 0x6f, 0x64, 0x20, 0x74, 0x65, 0x6d, 0x70, 0x6f, 0x72,
  0x20, 0x69, 0x6e, 0x63, 0x69, 0x64, 0x69, 0x64, 0x75, 0x6e, 0x74, 0x20,
  0x75, 0x74, 0x20, 0x6c, 0x61, 0x62, 0x6f, 0x72, 0x65, 0x20, 0x65, 0x74,
  0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x65, 0x20, 0x6d, 0x61, 0x67, 0x6e,
  0x61, 0x20, 0x61, 0x6c, 0x69, 0x71, 0x75, 0x61, 0x2e, 0x20, 0x55, 0x74,
  0x20, 0x65, 0x6e, 0x69, 0x6d, 0x20, 0x61, 0x64, 0x20, 0x6d, 0x69, 0x6e,
  0x69, 0x6d, 0x20, 0x76, 0x65, 0x6e, 0x69, 0x61, 0x6d, 0x2c, 0x20, 0x71,
  0x75, 0x69, 0x73, 0x20, 0x6e, 0x6f, 0x73, 0x74, 0x72, 0x75, 0x64, 0x20,
  0x65, 0x78, 0x65, 0x72, 0x63, 0x69, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e,
  0x20, 0x75, 0x6c, 0x6c, 0x61, 0x6d, 0x63, 0x6f, 0x20, 0x6c, 0x61, 0x62,
  0x6f, 0x72, 0x69, 0x73, 0x20, 0x6e, 0x69, 0x73, 0x69, 0x20, 0x75, 0x74,
  0x20, 0x61, 0x6c, 0x69, 0x71, 0x75, 0x69, 0x70, 0x20, 0x65, 0x78, 0x20,
  0x65, 0x61, 0x20, 0x63, 0x6f, 0x6d, 0x6d, 0x6f, 0x64, 0x6f, 0x20, 0x63,
  0x6f, 0x6e, 0x73, 0x65, 0x71, 0x75, 0x61, 0x74, 0x2e, 0x20, 0x44, 0x75,
  0x69, 0x73, 0x20, 0x61, 0x75, 0x74, 0x65, 0x20, 0x69, 0x72, 0x75, 0x72,
  0x65, 0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x69, 0x6e, 0x20, 0x72,
  0x65, 0x70, 0x72, 0x65, 0x68, 0x65, 0x6e, 0x64, 0x65, 0x72, 0x69, 0x74,
  0x20, 0x69, 0x6e, 0x20, 0x76, 0x6f, 0x6c, 0x75, 0x70, 0x74, 0x61, 0x74,
  0x65, 0x20, 0x76, 0x65, 0x6c, 0x69, 0x74, 0x20, 0x65, 0x73, 0x73, 0x65,
  0x20, 0x63, 0x69, 0x6c, 0x6c, 0x75, 0x6d, 0x20, 0x64, 0x6f, 0x6c, 0x6f,
  0x72, 0x65, 0x20, 0x65, 0x75, 0x20, 0x66, 0x75, 0x67, 0x69, 0x61, 0x74,
  0x20, 0x6e, 0x75, 0x6c, 0x6c, 0x61, 0x20, 0x70, 0x61, 0x72, 0x69, 0x61,
  0x74, 0x75, 0x72, 0x2e, 0x20, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x65,
  0x75, 0x72, 0x20, 0x73, 0x69, 0x6e, 0x74, 0x20, 0x6f, 0x63, 0x63, 0x61,
  0x65, 0x63, 0x61, 0x74, 0x20, 0x63, 0x75, 0x70, 0x69, 0x64, 0x61, 0x74,
  0x61, 0x74, 0x20, 0x6e, 0x6f, 0x6e, 0x20, 0x70, 0x72, 0x6f, 0x69, 0x64,
  0x65, 0x6e, 0x74, 0x2c, 0x20, 0x73, 0x75, 0x6e, 0x74, 0x20, 0x69, 0x6e,
  0x20, 0x63, 0x75, 0x6c, 0x70, 0x61, 0x20, 0x71, 0x75, 0x69, 0x20, 0x6f,
  0x66, 0x66, 0x69, 0x63, 0x69, 0x61, 0x20, 0x64, 0x65, 0x73, 0x65, 0x72,
  0x75, 0x6e, 0x74, 0x20, 0x6d, 0x6f, 0x6c, 0x6c, 0x69, 0x74, 0x20, 0x61,
  0x6e, 0x69, 0x6d, 0x20, 0x69, 0x64, 0x20, 0x65, 0x73, 0x74, 0x20, 0x6c,
  0x61, 0x62, 0x6f, 0x72, 0x75, 0x6d, 0x2e, 0x22, 0x0a, 0x20, 0x20, 0x20,
  0x20, 0x22, 0x4c, 0x6f, 0x72, 0x65, 0x6d, 0x20, 0x69, 0x70, 0x73, 0x75,
  0x6d, 0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x73, 0x69, 0x74, 0x20,
  0x61, 0x6d, 0x65, 0x74, 0x2c, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x65, 0x63,
  0x74, 0x65, 0x74, 0x75, 0x72, 0x20, 0x61, 0x64, 0x69, 0x70, 0x69, 0x73,
  0x63, 0x69, 0x6e, 0x67, 0x20, 0x65, 0x6c, 0x69, 0x74, 0x2c, 0x20, 0x73,
  0x65, 0x64, 0x20, 0x64, 0x6f, 0x20, 0x65, 0x69, 0x75, 0x73, 0x6d, 0x6f,
  0x64, 0x20, 0x74, 0x65, 0x6d, 0x70, 0x6f, 0x72, 0x20, 0x69, 0x6e, 0x63,
  0x69, 0x64, 0x69, 0x64, 0x75, 0x6e, 0x74, 0x20, 0x75, 0x74, 0x20, 0x6c,
  0x61, 0x62, 0x6f, 0x72, 0x65, 0x20, 0x65, 0x74, 0x20, 0x64, 0x6f, 0x6c,
  0x6f, 0x72, 0x65, 0x20, 0x6d, 0x61, 0x67, 0x6e, 0x61, 0x20, 0x61, 0x6c,
  0x69, 0x71, 0x75, 0x61, 0x2e, 0x20, 0x55, 0x74, 0x20, 0x65, 0x6e, 0x69,
  0x6d, 0x20, 0x61, 0x64, 0x20, 0x6d, 0x69, 0x6e, 0x69, 0x6d, 0x20, 0x76,
  0x65, 0x6e, 0x69, 0x61, 0x6d, 0x2c, 0x20, 0x71, 0x75, 0x69, 0x73, 0x20,
  0x6e, 0x6f, 0x73, 0x74, 0x72, 0x75, 0x64, 0x20, 0x65, 0x78, 0x65, 0x72,
  0x63, 0x69, 0x74, 0x61, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x75, 0x6c, 0x6c,
  0x61, 0x6d, 0x63, 0x6f, 0x20, 0x6c, 0x61, 0x62, 0x6f, 0x72, 0x69, 0x73,
  0x20, 0x6e, 0x69, 0x73, 0x69, 0x20, 0x75, 0x74, 0x20, 0x61, 0x6c, 0x69,
  0x71, 0x75, 0x69, 0x70, 0x20, 0x65, 0x78, 0x20, 0x65, 0x61, 0x20, 0x63,
  0x6f, 0x6d, 0x6d, 0x6f, 0x64, 0x6f, 0x20, 0x63, 0x6f, 0x6e, 0x73, 0x65,
  0x71, 0x75, 0x61, 0x74, 0x2e, 0x20, 0x44, 0x75, 0x69, 0x73, 0x20, 0x61,
  0x75, 0x74, 0x65, 0x20, 0x69, 0x72, 0x75, 0x72, 0x65, 0x20, 0x64, 0x6f,
  0x6c, 0x6f, 0x72, 0x20, 0x69, 0x6e, 0x20, 0x72, 0x65, 0x70, 0x72, 0x65,
  0x68, 0x65, 0x6e, 0x64, 0x65, 0x72, 0x69, 0x74, 0x20, 0x69, 0x6e, 0x20,
  0x76, 0x6f, 0x6c, 0x75, 0x70, 0x74, 0x61, 0x74, 0x65, 0x20, 0x76, 0x65,
  0x6c, 0x69, 0x74, 0x20, 0x65, 0x73, 0x73, 0x65, 0x20, 0x63, 0x69, 0x6c,
  0x6c, 0x75, 0x6d, 0x20, 0x64, 0x6f, 0x6c, 0x6f, 0x72, 0x65, 0x20, 0x65,
  0x75, 0x20, 0x66, 0x75, 0x67, 0x69, 0x61, 0x74, 0x20, 0x6e, 0x75, 0x6c,
  0x6c, 0x61, 0x20, 0x70, 0x61, 0x72, 0x69, 0x61, 0x74, 0x75, 0x72, 0x2e,
  0x20, 0x45, 0x78, 0x63, 0x65, 0x70, 0x74, 0x65, 0x75, 0x72, 0x20, 0x73,
  0x69, 0x6e, 0x74, 0x20, 0x6f, 0x63, 0x63, 0x61, 0x65, 0x63, 0x61, 0x74,
  0x20, 0x63, 0x75, 0x70, 0x69, 0x64, 0x61, 0x74, 0x61, 0x74, 0x20, 0x6e,
  0x6f, 0x6e, 0x20, 0x70, 0x72, 0x6f, 0x69, 0x64, 0x65, 0x6e, 0x74, 0x2c,
  0x20, 0x73, 0x75, 0x6e, 0x74, 0x20, 0x69, 0x6e, 0x20, 0x63, 0x75, 0x6c,
  0x70, 0x61, 0x20, 0x71, 0x75, 0x69, 0x20, 0x6f, 0x66, 0x66, 0x69, 0x63,
  0x69, 0x61, 0x20, 0x64, 0x65, 0x73, 0x65, 0x72, 0x75, 0x6e, 0x74, 0x20,
  0x6d, 0x6f, 0x6c, 0x6c, 0x69, 0x74, 0x20, 0x61, 0x6e, 0x69, 0x6d, 0x20,
  0x69, 0x64, 0x20, 0x65, 0x73, 0x74, 0x20, 0x6c, 0x61, 0x62, 0x6f, 0x72,
  0x75, 0x6d, 0x2e, 0x22, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x62, 0x6f, 0x64,
  0x79, 0x3e, 0x0a, 0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a
};
unsigned int index_long_html_len = 1415;
static char *path_index_long_html = "/index_long.html";

int test_file_local_filesystem(void)
{
  http_localfs_init();
  http_localfs_filesystem_fp_t fp;

  //register default index file into the local file system.
  int retval = http_localfs_registerFile(path_index1_html, (char *)&index1_html, index1_html_len, 0);
  if (retval < 0)
  {
    printf(FAIL "test_file_local_filesystem(registerFile failed)\r\n");
  }
  printf(PASS "test_file_local_filesystem(rgister File)\r\n");
  //test fopen
  fp = http_localfs_fopen(path_index1_html);
  if (NULL == fp)
  {
    printf(FAIL "test_file_local_filesystem(fopen index)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fopen index)\r\n");

  //test content length using feof
  unsigned int i = 1;
  while (-1 != http_localfs_feof(fp))
  {
    http_localfs_fgetc(fp);
    i++;
  }
  if (index1_html_len != i)
  { //hard coded length of index file
    printf(FAIL "test_file_local_filesystem(content length(%d!=%d))\r\n", index1_html_len, i);
    return -1;
  }
  printf(PASS "test_file_local_filesystem(content Length)\r\n");
  http_localfs_fclose(fp);

  //test contents
  unsigned char fileContents[index1_html_len];
  fp = http_localfs_fopen(path_index1_html);
  i = 0;
  while (-1 != http_localfs_feof(fp))
  {
    fileContents[i] = (unsigned char)http_localfs_fgetc(fp);
    i++;
  }
  if (0 != strncmp((const char *)index1_html, (const char *)fileContents, index1_html_len - 1))
  {
    printf(FAIL "test_file_local_filesystem(content comparison)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(getc- content comparison)\r\n");

  http_localfs_fclose(fp);

  //fread test
  fp = http_localfs_fopen(path_index1_html);
  char fileReadBuffer[500];
  int readLength = http_localfs_fread((void *)&fileReadBuffer, 55, 1, fp);
  if (55 != readLength)
  {
    printf(FAIL "test_file_local_filesystem(read- length missmatch)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(read- lengthmissmatch)\r\n");
  if (0 != strncmp((const char *)index1_html, (const char *)fileReadBuffer, 55))
  {
    printf(FAIL "test_file_local_filesystem(read content comparison)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(read- content comparison)\r\n");

  //ty rto read more contents than remaining
  readLength = http_localfs_fread((void *)&fileReadBuffer, 100, 1, fp);
  if ((unsigned int)readLength != index1_html_len - 55)
  {
    printf(FAIL "test_file_local_filesystem(remaining read content length (%d,%d))\r\n",readLength,index1_html_len-55);
    return -1;
  }
  printf(PASS "test_file_local_filesystem(remaining read content length (%d,%d))\r\n",readLength,index1_html_len-55);
  //test remaining read contents
  if (0 != strncmp((const char *)&index1_html[55], (const char *)fileReadBuffer, readLength))
  {
    printf("%.*s\r\n",readLength,&index1_html[55]);
    printf("%.*s\r\n",readLength,fileReadBuffer);
    printf(FAIL "test_file_local_filesystem(remaining read content comparison(%d))\r\n",readLength);
    return -1;
  }
  printf(PASS "test_file_local_filesystem(remaining read content comparison(%d))\r\n",readLength);

  //try to read contents when it is already at EOF
  readLength = http_localfs_fread((void *)&fileReadBuffer, 100, 1, fp);
  if (-1 != readLength)
  {
    printf(FAIL "test_file_local_filesystem(over read test failure)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(read - over read test)\r\n");
  http_localfs_fclose(fp);

  fp = http_localfs_fopen(path_index1_html);
  int retVal = http_localfs_fseek(fp, 10, SEEK_SET);
  if ((0 != retVal) || (10 != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek SEEK_SET)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek offset SEEK_SET)\r\n");

  //test long seek set
  retVal = http_localfs_fseek(fp, 100, SEEK_SET);
  if ((0 != retVal) || ((index1_html_len - 1) != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek long SEEK_SET)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek long SEEK_SET)\r\n");

  //test seek end
  retVal = http_localfs_fseek(fp, -57, SEEK_END);
  if ((0 != retVal) || (1 != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek SEEK_END)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek SEEK_END)\r\n");

  //test seek end
  retVal = http_localfs_fseek(fp, -57, SEEK_END);
  if ((0 != retVal) || (0 != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek long SEEK_END)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek long SEEK_END)\r\n");

  //test to open nonexistant file
  fp = http_localfs_fopen("/jibberish");
  if (NULL != fp)
  {
    printf(FAIL "test_file_local_filesystem(fopen Jibberish)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fopen - jibberish)\r\n");

  //test to close null FP
  if (HTTP_SUCCESS == http_localfs_fclose(fp))
  {
    printf(FAIL "test_file_local_filesystem(fclose Jibberish)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fclose - jibberish)\r\n");

  //deinit the filesystem
  if (HTTP_SUCCESS != http_localfs_deinit())
  {
    printf(FAIL "test_file_local_filesystem(fs deinit)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fs deinit)\r\n");

  printf(PASS ">>test_file_local_filesystem<<\r\n");
  return 0;
}

/*wrapper functions for type sanity. 
if this is not done casting fp to void will cause compiler warnings
*/
void *http_localfs_fopen_w(const char *filename);
int http_localfs_fclose_w(void *fp);
size_t http_localfs_fread_w(void *ptr, size_t size, size_t nmemb, void *fp);
int http_localfs_fgetc_w(void *fp);
int http_localfs_fseek_w(void *fp, long offset, int whence);
int http_localfs_feof_w(void *fp);

void *http_localfs_fopen_w(const char *filename) { return (void *)http_localfs_fopen(filename); }
int http_localfs_fclose_w(void *fp) { return http_localfs_fclose((http_localfs_filesystem_fp_t)fp); }
size_t http_localfs_fread_w(void *ptr, size_t size, size_t nmemb, void *fp) { return http_localfs_fread(ptr, size, nmemb, (http_localfs_filesystem_fp_t)fp); }
int http_localfs_fgetc_w(void *fp) { return http_localfs_fgetc((http_localfs_filesystem_fp_t)fp); }
int http_localfs_fseek_w(void *fp, long offset, int whence) { return http_localfs_fseek((http_localfs_filesystem_fp_t)fp, offset, whence); }
int http_localfs_feof_w(void *fp) { return http_localfs_feof((http_localfs_filesystem_fp_t)fp); }

int test_http_file(void)
{
  http_file_fops_t localFSFops;
  //init all to null

  http_localfs_deinit(); //just in case previous test left it in stale state
  http_localfs_init();

  //register default index file into the local file system.
  int retval = http_localfs_registerFile(path_index1_html, (char *)&index1_html, index1_html_len, 0);
  if (retval < 0)
  {
    printf(FAIL "test_http_file(registerFile failed)\r\n");
  }
  printf(PASS "test_http_file(rgister File)\r\n");

  http_file_init_fopsStruct(&localFSFops);
  printf(PASS "test_http_file(init fops struct fops)\r\n");
  localFSFops.fopen = http_localfs_fopen_w;
  localFSFops.fclose = http_localfs_fclose_w;
  localFSFops.fread = http_localfs_fread_w;
  localFSFops.fgetc = http_localfs_fgetc_w;
  localFSFops.fseek = http_localfs_fseek_w;
  localFSFops.feof = http_localfs_feof_w;

  http_file_register_fops(localFSFops);
  printf(PASS "test_http_file(register fops)\r\n");

  //now try calling the fops via the master http_file_fops
  void *fp = http_file_fops.fopen(path_index1_html);
  if (NULL == fp)
  {
    printf(FAIL "test_http_file(fopen index)\r\n");
    return -1;
  }
  printf(PASS "test_http_file(fopen index)\r\n");

  if (0 != http_file_fops.fclose(fp))
  {
    printf(FAIL "test_http_file(fclose index)\r\n");
    return -1;
  }
  printf(PASS "test_http_file(fclose index)\r\n");

  printf(PASS ">>test_http_file<<\r\n");
  return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int http_net_test_read(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
int http_net_test_write(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
void http_net_test_disconnect(int socket);

int http_net_test_read(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs)
{
  if ((0 > socket) || (NULL == readBuffer) || (0 == readBufferLength) || (0 > timeoutMs))
  {
    return -1;
  }
  return 0;
}
int http_net_test_write(int socket, unsigned char *writeBuffer, int writeBufferLength, int timeoutMs)
{
  if ((0 > socket) || (NULL == writeBuffer) || (0 == writeBufferLength) || (0 > timeoutMs))
  {
    return -1;
  }
  return 0;
}
void http_net_test_disconnect(int socket)
{
  if (0 > socket)
  {
  }
}

//http_net_test
int test_http_net(void)
{
  http_net_netops_t http_net_test_netops;
  http_net_init_netopsStruct(&http_net_test_netops);
  printf(PASS "test_http_net(netops struct init)\r\n");

  int socket = 2;
  http_net_test_netops.http_net_read = http_net_test_read;
  http_net_test_netops.http_net_write = http_net_test_write;
  http_net_test_netops.http_net_disconnect = http_net_test_disconnect;

  http_net_netops_t *httpNetops = http_net_register_netops(http_net_test_netops);
  printf(PASS "test_http_net(netops registration)\r\n");

  unsigned char readBuffer[10];
  httpNetops->http_net_read(socket, (unsigned char *)&readBuffer, 10, 0);
  printf(PASS "test_http_net(netops read call)\r\n");

  httpNetops->http_net_write(socket, (unsigned char *)&readBuffer, 10, 0);
  printf(PASS "test_http_net(netops write call)\r\n");

  httpNetops->http_net_disconnect(socket);
  printf(PASS "test_http_net(netops disconnect call)\r\n");

  http_net_deregister_netops();
  printf(PASS "test_http_net(netops de-registration)\r\n");

  printf(PASS ">>test_http_net<<\r\n");
  return 0;
}

int http_server_dummy_read(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
int http_server_dummy_write(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
void http_server_dummy_disconnect(int socket);

int http_server_dummy_read(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs)
{
  unsigned char sock1RequestBuffer[] = "GET /ta.gs/ref_htt%20%20pmethods.html\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  unsigned char sock2RequestBuffer[] = "GET /index1.html\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  unsigned char sock3RequestBuffer[] = "GET /ta.gs/ref_htt%20%20pmethods.cgi\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  unsigned char sock4RequestBuffer[] = "GET /cgi/test.cgi\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  unsigned char sock5RequestBuffer[] = "GET /index_long.html\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";

  if ((0 > socket) || (NULL == readBuffer) || (0 == readBufferLength) || (0 > timeoutMs))
  {
    return -1;
  }
  switch (socket)
  {
  case 1: //non-existetn file
    memcpy((void *)readBuffer, (void *)&sock1RequestBuffer, sizeof(sock1RequestBuffer));
    return (int)sizeof(sock1RequestBuffer);
    break;
  case 2: //index.html
    memcpy((void *)readBuffer, (void *)&sock2RequestBuffer, sizeof(sock2RequestBuffer));
    return (int)sizeof(sock2RequestBuffer);
    break;
  case 3:
    memcpy((void *)readBuffer, (void *)&sock3RequestBuffer, sizeof(sock3RequestBuffer));
    return (int)sizeof(sock3RequestBuffer);
    break;
  case 4:
    memcpy((void *)readBuffer, (void *)&sock4RequestBuffer, sizeof(sock4RequestBuffer));
    return (int)sizeof(sock3RequestBuffer);
    break;
  case 5:
    memcpy((void *)readBuffer, (void *)&sock5RequestBuffer, sizeof(sock5RequestBuffer));
    return (int)sizeof(sock3RequestBuffer);
    break;

  default:
    return -1;
    break;
  }

  return -1;
}
int http_server_dummy_write(int socket, unsigned char *writeBuffer, int writeBufferLength, int timeoutMs)
{
  char *sock1RetString = "HTTP/1.1 404 Not Found\r\n\r\n";
  char *sock2RetHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 59\r\n\r\n";
  char *sock4RetHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 4\r\n\r\n" ;
  static int headerBody = 0;
  size_t compLen;
  if ((0 > socket) || (NULL == writeBuffer) || (0 == writeBufferLength) || (0 > timeoutMs))
  {
    return -1;
  }
  switch (socket)
  {
  case 1:
    compLen = sizeof(sock1RetString);
    if (0 != strncmp((char *)writeBuffer, sock1RetString, compLen))
    {
      printf(FAIL "test_http_server (HTML 404 filenot found)\r\n");
      return -1;
    }
    printf(PASS "test_http_server (HTML 404 filenot found)\r\n");
    break;
  case 2:
    if (0 == headerBody)
    { //expecting header to be written
      compLen = sizeof(sock2RetHeader);
      if (0 != strncmp(sock2RetHeader, (char *)writeBuffer, compLen))
      {
        printf(FAIL "test_http_server (HTML 200 OK header test)\r\n");
        return -1;
      }
      printf(PASS "test_http_server (HTML 200 OK header test)\r\n");
      headerBody += 1; //next expect body
      return 0;
    }
    else if (1 == headerBody)
    {
      headerBody = 0; //set for next test
      if (0 != strncmp((char *)writeBuffer, (char *)index1_html, index1_html_len))
      {
        printf(FAIL "test_http_server (HTML 200 OK body test (%d,%d))\r\n",index1_html_len, writeBufferLength);
        return -1;
      }
      printf(PASS "test_http_server (HTML 200 OK body test(%d,%d))\r\n", index1_html_len, writeBufferLength);
      return 0;
    }
    break;
  case 3:
    compLen = sizeof(sock1RetString);
    if (0 != strncmp((char *)writeBuffer, sock1RetString, compLen))
    {
      printf(FAIL "test_http_server (404 filenot found - cgi)\r\n");
      return -1;
    }
    printf(PASS "test_http_server (404 filenot found-cgi)\r\n");
    break;
  case 4:
    if (0 == headerBody)
    {
      headerBody = 1; //next expect body
      compLen = sizeof(sock4RetHeader);
      if (0 != strncmp(sock4RetHeader, (char *)writeBuffer, compLen))
      {
        printf(FAIL "test_http_server (CGI HTML 200 OK header test)\r\n");
        return -1;
      }
      printf(PASS "test_http_server (CGI HTML 200 OK header test)\r\n");
      return 0;
    }
    else if (1 == headerBody)
    {
      headerBody = 0; //set for next test
      if (0 != strncmp((char *)writeBuffer, "0xA0", 4))
      {
        printf(FAIL "test_http_server (CGI - HTML 200 OK body test)\r\n");
        return -1;
      }
      printf(PASS "test_http_server (CGI - HTML 200 OK body test(%d,%d))\r\n", index1_html_len, writeBufferLength);
      return 0;
    }
    break;
    case 5:
      //printf("socket write stub (sock: %d, len: %d)\r\n", socket, writeBufferLength);
      //printf("%.*s", writeBufferLength, writeBuffer);
      //TODO: assumed pass since we are yet to write full test case here. 
    break;
  default:
    return -1;
    break;
  }
  //printf("socket write stub (sock: %d, len: %d)\r\n", socket, writeBufferLength);
  //printf("%.*s", writeBufferLength, writeBuffer);

  return -1;
}
void http_server_dummy_disconnect(int socket)
{
  if (socket <= 0)
  {
    printf(FAIL "Disconnecting socket (%d)\r\n", socket);
  }
}

char *serverTest_cgiPathFunction_ret = "0xA0";
int httpServerTest_cgiPathFunction(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength);
int httpServerTest_cgiPathFunction(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp(CGIPath, "/cgi/test.cgi"))
    return -1;
  if ((bufferLength <= 0) || NULL == replacerBuffer)
    return -1;
  strncpy(replacerBuffer, serverTest_cgiPathFunction_ret, strlen(serverTest_cgiPathFunction_ret));
  return strlen(serverTest_cgiPathFunction_ret);
}
//http_server_test
int test_http_server(void)
{
  //deinit and init the FS
  http_file_fops_t localFSFops;
  http_localfs_deinit(); //just in case previous test left it in stale state
  http_localfs_init();
  char *serverTestCGIPath = "/cgi/test.cgi";
  //register default index file into the local file system.
  int retval = http_localfs_registerFile(path_index1_html, (char *)&index1_html, index1_html_len, 0);
  if (retval < 0)
  {
    printf(FAIL "test_http_server(registerFile failed)\r\n");
  }
  retval = http_localfs_registerFile(path_index_long_html, (char *)&index_long_html, index_long_html_len, 0);
  if (retval < 0)
  {
    printf(FAIL "test_http_server(register long File failed)\r\n");
  }
  //register fops. reusing fops wrapers from fs test
  http_file_init_fopsStruct(&localFSFops);
  localFSFops.fopen = http_localfs_fopen_w;
  localFSFops.fclose = http_localfs_fclose_w;
  localFSFops.fread = http_localfs_fread_w;
  localFSFops.fgetc = http_localfs_fgetc_w;
  localFSFops.fseek = http_localfs_fseek_w;
  localFSFops.feof = http_localfs_feof_w;
  http_file_register_fops(localFSFops);
  //register stub netops
  http_net_netops_t http_net_test_netops;
  http_net_init_netopsStruct(&http_net_test_netops);

  http_net_test_netops.http_net_read = http_server_dummy_read;
  http_net_test_netops.http_net_write = http_server_dummy_write;
  http_net_test_netops.http_net_disconnect = http_server_dummy_disconnect;
  http_net_netops_t *httpNetops = http_net_register_netops(http_net_test_netops);

  //socket1 test - non-existant file
  if (0 > http_server(1, httpNetops))
  {
    printf(FAIL "test_http_server(sock 1)\r\n");
    return -1;
  }
  //socket2 test - index1.html from test page
  if (0 > http_server(2, httpNetops))
  {
    printf(FAIL "test_http_server(sock 2)\r\n");
    return -1;
  }
  //socket3 test - non existant CGI page
  if (0 > http_server(3, httpNetops))
  {
    printf(FAIL "test_http_server(sock 3)\r\n");
    return -1;
  }

  //now call the server for CGI test socket
  if (0 > http_server(4, httpNetops))
  {
    printf(FAIL "test_http_server(sock 4)\r\n");
    return -1;
  }

  //register a CGI path function
  http_CGI_pathFunction_t *cgiPathHandle2;
  cgiPathHandle2 = http_CGI_register_pathFunction(serverTestCGIPath, httpServerTest_cgiPathFunction, HTTP_contentType_plaintext);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_http_server(http_CGI_register_pathFunction)");
    return -1;
  }

  //now call the server for CGI test socket
  if (0 > http_server(5, httpNetops))
  {
    printf(FAIL "test_http_server(sock 4)\r\n");
    return -1;
  }

  printf(PASS ">>test_http_server<<\r\n");
  return 0;
}

int main(void)
{
  //testing request method and path parsing
  int retval = 0;
  if (0 != test_methodFileType())
    retval = -1;
  if (0 != test_SSIStringRegistration())
    retval = -2;
  if (0 != test_SSIStringReplacementCB())
    retval = -3;
  if (0 != test_CGI_registration())
    retval = -4;
  if (0 != test_CGI_exec())
    retval = -5;
  if (0 != test_response_fileType())
    retval = -5;
  if (0 != test_response_contentType())
    retval = -6;
  if (0 != test_response_header())
    retval = -7;
  if (0 != test_file_local_filesystem())
    retval = -8;
  if (0 != test_http_file())
    retval = -9;
  if (0 != test_http_net())
    retval = -10;
  if (0 != test_http_server())
    retval = -11;
  if (0 == retval)
  {
    printf(PASS "****************ALL TESTS PASSED****************\r\n\r\n");
  }
  else
  {
    printf(FAIL "!!!!!!!!!!!!!!!!SOME TEST(s) FAILED!!!!!!!!!!!!!!!!\r\n\r\n");
  }
  return retval;
}
