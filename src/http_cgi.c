#include <string.h>
#include <stdlib.h>
#include "http_cgi.h"
#include "http_config.h"
#include "http_common.h"

/*defining this as array for the following reasons
1) lookup speed is better than linked list
2) configuration is static and fixed at compile time. This can be adjusted in http_config.h 
*/
http_CGI_pathFunction_t CGI_path[HTTP_MAX_CGI_SIZE]; //hoping compiler to do its job and init to 0

int http_CGI_exec_pathFunction(char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
    int i;
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    { //find an empty slot and fill in the registration
        if (NULL != CGI_path[i].CGI_path)
        {
            if (0 == strcmp(CGIPath, CGI_path[i].CGI_path))
            {
                return CGI_path[i].CGI_pathFunction(CGIPath, replacerBuffer, bufferLength);
            }
        }
    }
    return -1;
}

http_CGI_pathFunctionHandle_t http_CGI_register_pathFunction(const char *CGIPath, http_CGI_pathFunction_cb CGIPathFunctionCb)
{
    //find a uninitialized array element
    if ((NULL == CGIPath) || (NULL == CGIPathFunctionCb))
    {
        PRINT_ERROR("ERROR: http_CGI_register_pathFunction - NULL CGIPath or CB (%p)\r\n",(void*)CGIPath);
        return 0;
    }
    else
    {
        int i = 0;
        for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
        { //find an empty slot and fill in the registration
            if (NULL == CGI_path[i].CGI_path)
            {
                //allocate memory and copy string to it.
                CGI_path[i].CGI_path = (char *)malloc((size_t)strlen(CGIPath) + 1);
                strncpy(CGI_path[i].CGI_path, CGIPath, strlen(CGIPath));
                CGI_path[i].CGI_path[strlen(CGIPath)] = 0;

                CGI_path[i].CGI_pathFunction = CGIPathFunctionCb;
                return &CGI_path[i];
            }
        }
        PRINT_ERROR("ERROR: http_CGI_register_pathFunction - no more slots to register(%d)\r\n",i);
        return NULL;
    }
    return NULL; //Just a safety net.
}

void http_CGI_deRegister_pathFunction(http_CGI_pathFunctionHandle_t deregisterHandle)
{
    //free the strings?
    //make contents in array 0
    free(deregisterHandle->CGI_path);
    deregisterHandle->CGI_path = NULL;
    deregisterHandle->CGI_pathFunction = NULL;
    deregisterHandle = NULL;
}

//deregister all registrations in one-go. Useful to implement a shutdown function
void http_CGI_deRegister_all(void)
{
    int i = 0;
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    { //find an empty slot and fill in the registration
        if (0 != CGI_path[i].CGI_path)
        {
            //free the string memory from heap
            free(CGI_path[i].CGI_path);
            CGI_path[i].CGI_path = NULL;
            CGI_path[i].CGI_pathFunction = NULL;
        }
    }
}

//test function to print complete registration table. to be used only for debugging
void http_CGI_printPathFunctionTable(void)
{
    int i;
    printf("FUNCTION\t\tPATH\r\n");
    for (i = 0; i < HTTP_MAX_CGI_SIZE; i++)
    {
        printf("%p\t\t", (void *)CGI_path[i].CGI_pathFunction);
        printf("%s\r\n", CGI_path[i].CGI_path);
    }
    printf("==============================================================\r\n");
}