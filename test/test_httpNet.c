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