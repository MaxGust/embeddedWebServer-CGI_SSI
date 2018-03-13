#ifndef __HTTP_NET_H__
#define __HTTP_NET_H__

typedef int (*http_net_read_t) (http_net_network_t *http_net_network, unsigned char* readBuffer, int readBufferLength, int timeoutMs);
typedef int (*http_net_write_t) (http_net_network_t *http_net_network, unsigned char* readBuffer, int readBufferLength, int timeoutMs);
typedef void (*http_net_disconnect_t) (http_net_network_t *http_net_network);

//structure holding underlying network read write functions to plugin net to http server
typedef struct http_net_network_struct http_net_network_t;
struct http_net_network_struct
{
	int socket;
    http_net_read_t http_net_read;
    http_net_write_t http_net_write;
	http_net_disconnect_t http_net_disconnect;
};

#endif