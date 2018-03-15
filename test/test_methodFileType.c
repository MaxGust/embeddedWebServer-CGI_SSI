#include "test.h"

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