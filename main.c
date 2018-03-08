#include "helperFunctions.h"

int parseRquest_identifyRequest(char* requestBuffer);


int main()
{
  char[] requestbuffer="GET /index.htmli\r\ncache-control: no-cache\r\naccept-encoding: gzip, deflate\r\n\r\n";
  int parseRquest_identifyRequest(requestBuffer);
}



/*
   Function to parse incoming request buffer and identify the request method,
   and path. 

   At this initial stage , query strings and headers will not be handled since
   the initial version is targeting just GET requests. 
*/
typedef struct {
  
}http_request_t;
int parseRquest_identifyRequest(char* requestBuffer)
{

}
