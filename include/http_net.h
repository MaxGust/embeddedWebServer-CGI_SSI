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

#ifndef __HTTP_NET_H__
#define __HTTP_NET_H__

/*the idea here is that the platform code will start listening on a port, accept connections, 
bind it to a socket and then pass on that socket along with network read and write function pointers
to http_net to process requests comming in through that socket*/

typedef struct http_net_netops_struct http_net_netops_t;

typedef int (*http_net_read_t)(int socket, unsigned char *readBuffer, int readBufferLength, int timeoutMs);
typedef int (*http_net_write_t)(int socket, unsigned char *writeBuffer, int writeBufferLength, int timeoutMs);
typedef void (*http_net_disconnect_t)(int socket);

//structure holding underlying network read write functions to plugin net to http server

struct http_net_netops_struct
{
    http_net_read_t http_net_read;
    http_net_write_t http_net_write;
    http_net_disconnect_t http_net_disconnect;
};

void http_net_init_netopsStruct(http_net_netops_t *netops);
http_net_netops_t *http_net_register_netops(http_net_netops_t netops);
void http_net_deregister_netops(void);

#endif