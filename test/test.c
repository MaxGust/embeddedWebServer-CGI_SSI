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

