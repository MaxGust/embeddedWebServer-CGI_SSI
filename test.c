#include <stdio.h>
#include <string.h>
#include "helperFunctions.h"
#include "http_request_parser.h"
#include "http_common.h"
#include "http_config.h"
#include "http_SSI_replacer.h"
#include "Http_cgi.h"

#define PASS "\e[1;32mPASS:\e[0m\t"
#define FAIL "\e[1;31mFAIL:\e[0m\t"
/*test routine to check if method type , file path and file type are parsed properly*/
int test_methodFileType()
{
  char requestBuffer[] = "GET /ta.gs/ref_htt%20%20pmethods.shtm\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  int retVal = 0;
  http_request_t request;
  //printf("%s\r\n", requestBuffer);
  retVal = parseRquest_identifyRequest(requestBuffer, &request);
  if (HTTP_SUCCESS == retVal)
  {
    if ((httpFileType_SSI == request.fileType) && (GET == request.method) && (0 == strcmp(request.httpFilePath, "/ta.gs/ref_htt  pmethods.shtm")))
    {
      printf(PASS "test_methodFileType\r\n");
      return 0;
    }
    else
    {
      //printf("result\r\n\tfileType: %d\r\n\tmethod: %d\r\n\tpath:%s\r\n\r\n", request.fileType, request.method, request.httpFilePath);
      printf(FAIL "test_methodFileType(1)\r\n");
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
  strncpy(replacerBuffer, "timerValue is 200", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int sysStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  strncpy(replacerBuffer, "System is up and running", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int resetStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  strncpy(replacerBuffer, "Previous reset caused by Watchdog", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}

/*test routine to check if callback registration for SSI string is done properly*/
int test_SSIStringRegistration()
{
  char *testSSIString1 = "timerVal";
  char *testSSIString2 = "sysStatus";
  char *testSSIString3 = "resetStatus";

  char debugTablePrint = 0;
  http_SSI_replacer_t *SSIReplacementHandle1;
  SSIReplacementHandle1 = http_SSI_register_replacer(testSSIString1, timerVal_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle1)
  {
    printf(FAIL "test_SSIStringRegistration(1)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  http_SSI_replacer_t *SSIReplacementHandle2;
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString2, sysStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf(FAIL "test_SSIStringRegistration(2)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  http_SSI_replacer_t *SSIReplacementHandle3;
  SSIReplacementHandle3 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle3)
  {
    printf(FAIL "test_SSIStringRegistration(3)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  http_SSI_deRegister_replacer(SSIReplacementHandle2);
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  //multiple registrations of the same CB
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf(FAIL "test_SSIStringRegistration(4)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  printf(PASS "test_SSIStringRegistration\r\n");
  return 0;
}

/*unittest for replacement matching */
int test_SSIStringReplacementCB()
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
  strncpy(replacerBuffer, "exec1 Executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int exec2_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  strncpy(replacerBuffer, "exec2 Executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int exec3_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  strncpy(replacerBuffer, "exec3 executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}

/*unit test for CGI*/
int test_CGI_registration()
{
  char *cgiPath1 = "/CGI/exec1.cgi";
  char *cgiPath2 = "/bin/exec2.sh";
  char *cgiPath3 = "/exec3.exe";

  char debugTablePrint = 0;
  http_CGI_pathFunction_t *cgiPathHandle1;
  cgiPathHandle1 = http_CGI_register_pathFunction(cgiPath1, exec1_CGI_cb);
  if (NULL == cgiPathHandle1)
  {
    printf(FAIL "test_CGI(1)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_CGI_printPathFunctionTable();

  http_CGI_pathFunction_t *cgiPathHandle2;
  cgiPathHandle2 = http_CGI_register_pathFunction(cgiPath2, exec2_CGI_cb);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_CGI(2)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_CGI_printPathFunctionTable();

  http_CGI_pathFunction_t *cgiPathHandle3;
  cgiPathHandle3 = http_CGI_register_pathFunction(cgiPath3, exec3_CGI_cb);
  if (NULL == cgiPathHandle3)
  {
    printf(FAIL "test_CGI(3)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_CGI_printPathFunctionTable();

  http_CGI_deRegister_pathFunction(cgiPathHandle2);
  if (0 != debugTablePrint)
    http_CGI_printPathFunctionTable();

  //multiple registrations of the same CB
  cgiPathHandle2 = http_CGI_register_pathFunction(cgiPath3, exec3_CGI_cb);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_CGI(4)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_CGI_printPathFunctionTable();

  printf(PASS "test_CGI\r\n");
  return 0;
}

int test_CGI_exec()
{
  char stringArray[100];
  //try for exec of "/CGI/exec1.cgi"
  if (0 == http_CGI_exec_pathFunction("/CGI/exec1.cgi", (char *)&stringArray, sizeof(stringArray)))
  {
    if (0 != strcmp(stringArray, "exec1 Executed"))
    {
      printf(FAIL "test_CGI_exec(1)\r\n");
      return -1;
    }
  }

  //try for a non-existant SSI string
  if (0 == http_CGI_exec_pathFunction("nonExistantVal", (char *)&stringArray, sizeof(stringArray)))
  {
    printf(FAIL "test_CGI_exec(2)\r\n");
    return -1;
  }

  //deregister all replacers
  http_CGI_deRegister_all();

  printf(PASS "test_CGI_exec\r\n");
  return 0;
}

int main()
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
  return retval;
}
