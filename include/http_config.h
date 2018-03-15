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
#define HTTP_LOCALFS_INDEX

//server buffer sizes. All these are created locally per request. 
#define HTTP_SERVER_READ_BUFFER_SIZE (unsigned int)1024 //buffer used to read incoming request from network
#define HTTP_SERVER_HEADER_BUFFER_SIZE (unsigned int)256 //buffer used to form and later send response through socket. this can be lesser
#define HTTP_SERVER_FREAD_BUFFER_SIZE (unsigned int)1024 //buffer used to send contents. chunked vs regular send will be based on this vs filesize
#define HTTP_SERVER_CGI_BUFFER_SIZE (unsigned int)256 //buffer used to hold response from CGI.

//server read timeout
#define HTTP_SERVER_TIMOUT_MS 100

#endif