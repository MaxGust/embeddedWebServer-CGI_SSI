#include "http_net.h"
#include "http_common.h"
#include <stdio.h>
#include <string.h>

/*currently supporting only one file system at a time - should this go into http_server.c?*/
static http_net_netops_t http_net_netops;

/*init a plain fops structure*/
void http_net_init_netopsStruct(http_net_netops_t *netops)
{
    memset(netops, 0, sizeof(http_net_netops_t));
}
/*function to register fops to http server*/
http_net_netops_t *http_net_register_netops(http_net_netops_t netops)
{
    memcpy((void *)&http_net_netops, (void *)&netops, sizeof(http_net_netops_t));
    return &http_net_netops;
}

/*function to deregister fops from http server*/
void http_net_deregister_netops(void)
{
    memset(&http_net_netops, 0, sizeof(http_net_netops_t));
}
