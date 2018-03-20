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

#ifndef __HTTP_COMMON_H__
#define __HTTP_COMMON_H__

#include <stdio.h>
#include "http_config.h"

#define HTTP_SUCCESS (int)0
#define HTTP_FAILURE (int)-1
#define http_true 1
#define http_false 0

#if defined(DEBUG_ERROR) && DEBUG_ERROR > 0
#define PRINT_ERROR(fmt, ...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
                                      __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
#define PRINT_ERROR(fmt, ...) /* Don't do anything in release builds */
#endif

#endif