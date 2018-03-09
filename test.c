#include <stdio.h>
#include <string.h>
#include "helperFunctions.h"
#include "http_request_parser.h"
#include "http_common.h"
#include "http_config.h"
#include "http_replacer.h"

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
      printf("PASS:\ttest_methodFileType\r\n");
      return 0;
    }
    else
    {
      //printf("result\r\n\tfileType: %d\r\n\tmethod: %d\r\n\tpath:%s\r\n\r\n", request.fileType, request.method, request.httpFilePath);
      printf("FAIL:\ttest_methodFileType(1)\r\n");
      return -1;
    }
  }
  else
  {
    //printf("result\r\n\tfileType: %d\r\n\tmethod: %d\r\n\tpath:%s\r\n\r\n", request.fileType, request.method, request.httpFilePath);
    printf("FAIL:\ttest_methodFileType(2)\r\n");
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
    printf("FAIL:\ttest_SSIStringRegistration(1)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  http_SSI_replacer_t *SSIReplacementHandle2;
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString2, sysStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf("FAIL:\ttest_SSIStringRegistration(2)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  http_SSI_replacer_t *SSIReplacementHandle3;
  SSIReplacementHandle3 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle3)
  {
    printf("FAIL:\ttest_SSIStringRegistration(3)");
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
    printf("FAIL:\ttest_SSIStringRegistration(4)");
    return -1;
  }
  if (0 != debugTablePrint)
    http_SSI_printReplacerTable();

  printf("PASS:\ttest_SSIStringRegistration\r\n");
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
      printf("FAIL:\ttest_SSIStringReplacementCB(1)\r\n");
      return -1;
    }
  }

  //try for a non-existant SSI string
  if (0 == http_SSI_get_replacer_string("nonExistantVal", (char *)&stringArray, sizeof(stringArray)))
  {
    printf("FAIL:\ttest_SSIStringReplacementCB(2)\r\n");
    return -1;
  }

  //deregister all replacers
  http_SSI_deRegister_all();

  printf("PASS:\ttest_SSIStringReplacementCB\r\n");
  return 0;
}
int main()
{
  //testing request method and path parsing
  test_methodFileType();
  test_SSIStringRegistration();
  test_SSIStringReplacementCB();
  return 0;
}
