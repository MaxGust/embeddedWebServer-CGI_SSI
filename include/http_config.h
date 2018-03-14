#ifndef __HTTP_CONFIG_H__
#define __HTTP_CONFIG_H__

//#define DEBUG_ERROR 0 //this will be passed as build environment variable

//Max length of path supported by the system including string termination
#define HTTP_MAX_PATH_LENGTH 100

//Max length of method string including termination
#define HTTP_MAX_METHOD_LENGTH 8

//Max number of SSI strings supported
#define HTTP_MAX_SSI_SIZE 5
//Max number of CGIs supported
#define HTTP_MAX_CGI_SIZE 5

//populate a default index for local FS
#define HTTP_LOCALFS_INDEX

//server buffer size
#define HTTP_SERVER_READ_BUFFER_SIZE (unsigned int)1024
#define HTTP_SERVER_HEADER_BUFFER_SIZE (unsigned int)256 //this can be lesser
#define HTTP_SERVER_FREAD_BUFFER_SIZE (unsigned int)1024

//server read timeout
#define HTTP_SERVER_TIMOUT_MS 100

#endif