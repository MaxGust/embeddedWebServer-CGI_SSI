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

#ifndef __HTTP_FILE_H__
#define __HTTP_FILE_H__
#include <stdio.h>

/*
Uses standard terminology and signature as standard c file operations
expects same behaviour as standard C file operations
some quick references: 
    EOF = -1
    whence = SEEK_SET,SEEK_CUR or SEEK_END from stdio.h
file pointer (fp) is cast to void* to support different FS implementations
*/

typedef int (*http_file_fclose_t)(void *fp);
typedef int (*http_file_fgetc_t)(void *fp);
typedef int (*http_file_feof_t)(void *fp);
typedef void* (*http_file_fopen_t)(const char *filename); //returns file pointer (fp)
typedef int (*http_file_fseek_t)(void *fp, long offset, int whence);
typedef size_t (*http_file_fread_t)(void *ptr, size_t size, size_t nmemb, void *fp);

typedef struct
{
    http_file_fopen_t fopen;
    http_file_fclose_t fclose;
    http_file_fread_t fread;
    http_file_fgetc_t fgetc;
    http_file_fseek_t fseek;
    http_file_feof_t eof;
} http_file_fops_t; //type to register underlying file system fops to the HTTP server.

//global variable used to access fops by http server
extern http_file_fops_t http_file_fops;

//deregister all fops and make the structure NULL
void http_file_deregister_fops(void);

//register fops to teh http server
int http_file_register_fops(http_file_fops_t fops);

//make a new fops structure contents all NULL
void http_file_init_fopsStruct(http_file_fops_t *fops);

#endif