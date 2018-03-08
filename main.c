#include <stdio.h>
#include "helperFunctions.h"
#include "http_request_parser.h"




int main()
{
  char requestBuffer[]="PUT /ta.gs/ref_htt%20%20pmethods.sht\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  int retVal=0;
  http_request_t request;
  printf("%s\r\n",requestBuffer);
  retVal = parseRquest_identifyRequest(requestBuffer,&request);

  printf("result\r\n\tfileType: %d\r\n\tmethod: %d\r\n\tpath:%s\r\n\r\n",request.fileType,request.method,request.httpFilePath);
}

