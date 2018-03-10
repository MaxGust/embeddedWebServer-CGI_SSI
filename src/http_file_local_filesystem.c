#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "http_file_local_filesystem.h"
#include "http_response.h"
#include "http_common.h"
#include "http_config.h"

static http_file_filesystem_file_t http_local_filesystem[HTTP_LOCAL_FILESYSTEM_NUMFILES];
static unsigned int fileIndex = 0;

//arrays created using xxd tool.
//python xxd toot to test:L https://gist.githubusercontent.com/rakete/c6f7795e30d5daf43bb600abc06a9ef4/raw/1d9055f342b5d9c5a284a408859545542a9f4eae/xxd.py

//index.html
static unsigned char index_html[] = {
    0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x62, 0x6f,
    0x64, 0x79, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x31, 0x3e,
    0x48, 0x45, 0x4c, 0x4c, 0x4f, 0x20, 0x57, 0x4f, 0x52, 0x4c, 0x44, 0x3c,
    0x2f, 0x48, 0x31, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x62, 0x6f, 0x64,
    0x79, 0x3e, 0x0a, 0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a};
static unsigned int index_html_len = 59;
static char *path_index_html = "/index.html";

/*initialize filesystem . increase array size and populate details below to add it to FS*/
int http_localfs_init(void)
{
    //make the filesystem null.
    http_localfs_registerFile(path_index_html, (char *)&index_html, index_html_len, 0);
    return HTTP_SUCCESS;
}

//file path should be static string
int http_localfs_registerFile(const char *filePath, char *file, unsigned int fileLength, http_response_fileType_t optFileType)
{
    if(fileIndex!=(HTTP_LOCAL_FILESYSTEM_NUMFILES)){
        http_local_filesystem[fileIndex].fileNumber = fileIndex;
        http_local_filesystem[fileIndex].filePath = filePath;
        http_local_filesystem[fileIndex].file = (char *)&file;
        http_local_filesystem[fileIndex].fileLength = fileLength;
        http_local_filesystem[fileIndex].optFileType = optFileType;

        fileIndex++;
        return HTTP_SUCCESS;
    }
    else{
        PRINT_ERROR("fileSystem Full\r\n");
        return HTTP_FAILURE;
    }
}

//returns a file pointer
http_file_filesystem_fp_t http_localfs_fopen(const char *fileName)
{
    unsigned int i;
    for (i = 0; i < fileIndex; i++)
    {
        if (0 == strcmp(http_local_filesystem[i].filePath, fileName))
        {   
            http_file_filesystem_fp_t fp;
            fp = (http_file_filesystem_fp_t)malloc(sizeof(http_file_filesystem_fpRoot_t));
            fp->fileNumber = i;
            fp->filePosition = 0;
            return fp;
        }
    }
    return NULL;
}
//int http_localfs_fclose() //free the fp
//int http_localfs_fread()
//int http_localfs_fgetc()
//int http_localfs_ls()