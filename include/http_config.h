
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

#ifndef __HTTP_CONFIG_H__
#define __HTTP_CONFIG_H__

//#define DEBUG_ERROR 0 //this will be passed as build environment variable

//Max length of path supported by the system including string termination
#define HTTP_MAX_PATH_LENGTH 100

//Max length of method string including termination
#define HTTP_MAX_METHOD_LENGTH 8

//Max number of SSI strings supported
#define HTTP_MAX_SSI_COUNT 5
//max length of an SSI string in html
#define HTTP_MAX_SSI_LENGTH 15
//max length of a SSI replacement string 
#define HTTP_MAX_SSI_REPLACE_LENGTH 150

//maximum occurance of an SSI string per read buffer
#define HTTP_MAX_PER_SSI_COUNT 10
//Max number of CGIs supported
#define HTTP_MAX_CGI_SIZE 5

//populate a default index for local FS
//#define HTTP_LOCALFS_INDEX

//server buffer sizes. All these are created locally per request. 
#define HTTP_SERVER_READ_BUFFER_SIZE (unsigned int)1024 //buffer used to read incoming request from network
#define HTTP_SERVER_HEADER_BUFFER_SIZE (unsigned int)256 //buffer used to form and later send response through socket. this can be lesser
#define HTTP_SERVER_FREAD_BUFFER_SIZE (unsigned int)1024 //buffer used to send contents. chunked vs regular send will be based on this vs filesize
#define HTTP_SERVER_CGI_BUFFER_SIZE (unsigned int)256 //buffer used to hold response from CGI.

//root page to remap when requested path is "/"
#define HTTP_SERVER_ROOT_PAGE	"/index.html"

//server read timeout
#define HTTP_SERVER_TIMOUT_MS 100

#endif