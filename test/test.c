#include "test.h"


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
