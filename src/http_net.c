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

#include "http_net.h"
#include "http_common.h"
#include <stdio.h>
#include <string.h>

/*currently supporting only one network at a time - should this go into http_server.c?
    potentially many can be registersd and corresponding address can be returned.
*/
static http_net_netops_t http_net_netops;

/*init a plain fops structure*/
void http_net_init_netopsStruct(http_net_netops_t *netops)
{
    if (NULL != netops)
    {
        memset(netops, 0, sizeof(http_net_netops_t));
    }
}
/*function to register fops to http server*/
http_net_netops_t *http_net_register_netops(http_net_netops_t netops)
{
    memcpy((void *)&http_net_netops, (void *)&netops, sizeof(http_net_netops_t));
    return &http_net_netops;
}

/*function to deregister fops from http server*/
void http_net_deregister_netops(void)
{
    memset(&http_net_netops, 0, sizeof(http_net_netops_t));
}
