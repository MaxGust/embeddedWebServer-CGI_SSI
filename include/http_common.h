#ifndef __HTTP_COMMON_H__
#define __HTTP_COMMON_H__

#include <stdio.h>

#define HTTP_SUCCESS 0
#define http_true 1
#define http_false 0

#ifdef DEBUG_ERROR
#define PRINT_ERROR printf
#else
#define PRINT_ERROR
#endif

#endif