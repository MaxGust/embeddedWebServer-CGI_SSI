#ifndef __HTTP_COMMON_H__
#define __HTTP_COMMON_H__

#include <stdio.h>
#include "http_config.h"

#define HTTP_SUCCESS 0
#define http_true 1
#define http_false 0

#if defined(DEBUG_ERROR) && DEBUG_ERROR > 0
 #define PRINT_ERROR(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
    __FILE__, __LINE__, __func__, ##args)
#else
 #define PRINT_ERROR(fmt, args...) /* Don't do anything in release builds */
#endif



#endif