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

#include "http_file.h"
#include "http_common.h"
#include <stdio.h>
#include <string.h>

/*currently supporting only one file system at a time - should this go into http_server.c?*/
http_file_fops_t http_file_fops;

/*init a plain fops structure*/
void http_file_init_fopsStruct(http_file_fops_t *fops)
{
    memset(fops, 0, sizeof(http_file_fops_t));
}
/*function to register fops to http server*/
int http_file_register_fops(http_file_fops_t fops)
{
    memcpy((void*)&http_file_fops,(void*)&fops, sizeof(http_file_fops_t));
    return HTTP_SUCCESS;
}

/*function to deregister fops from http server*/
void http_file_deregister_fops(void)
{
   memset(&http_file_fops, 0, sizeof(http_file_fops_t));
}
