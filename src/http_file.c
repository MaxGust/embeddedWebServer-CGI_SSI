#include "http_file.h"
#include "http_common.h"
#include <stdio.h>
#include <string.h>

/*currently supporting only one file system at a time*/
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
