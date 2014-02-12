/*
* a simple server use libev
* libev.c
* Ò»¸ö¼òµ¥µÄ·þÎñÆ÷,²ÉÓÃlibev:¿Í»§¶Ë·¢À´µÄÊý¾Ý,·þÎñ¶ËÏìÓ¦"this is a libev server!" ×Ö·û´®
* compile:gcc -o libev -g libev.c -lev
* usage: ·þÎñ¶Ë£º ./libev  ¿Í»§¶Ë(ÔÚÍ¬Ò»Ì¨»úÆ÷ÉÏ)ÓÃnc¹¤¾ßÁ¬½Ó·þÎñ¶Ë:nc 127.0.0.1 8003
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <ev.h>

#include "rtsp.h"

#define MAXLEN 1023
#define PORT 8003
//#define ADDR_IP "127.0.0.1"
#define ADDR_IP "192.168.21.201"
#define ADDR_HOST "bnc_video"
#define ADDR_PORT "554"

struct ev_loop *rtsp_loop;

int rtsp_bind_addr(struct addrinfo *addr)
{
	struct sockaddr_in *rtsp_addr;
	ev_io *io;

	rtsp_addr=  (struct sockaddr_in *)addr->ai_addr;
	int rtsp_sock;
	if ((rtsp_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket create error");
		exit(1);
	}
	else{
		xlog(LOG_INF, "socket create success!");
	}
	//setnonblocking(rtsp_sock);
	int so_reuseaddr= 1;
	if(setsockopt(rtsp_sock, SOL_SOCKET,SO_REUSEADDR,&so_reuseaddr,sizeof(so_reuseaddr))< 0)
		goto open_error;

	/* Bind */
	if (bind(rtsp_sock, (struct sockaddr *)rtsp_addr, sizeof(struct sockaddr))== -1){
		xlog(LOG_ERR, "bind error!");
		exit(1);
	}
	else{
		xlog(LOG_INF, "IP BIND SUCCESS,IP:%s",ADDR_PORT);
	}

	/* Listen */
	if (listen(rtsp_sock, 1024) == -1){
		xlog(LOG_ERR, "listen error!");
		exit(1);
	}
	else{
		xlog(LOG_ERR, "LISTEN SUCCESS,PORT:%s",ADDR_PORT);
	}

	rtsp_socket_listener *listener;
	listener= g_slice_new0(rtsp_socket_listener);
	listener->fd= rtsp_sock;
	io= &listener->io;

	io->data= listener;
	ev_io_init(io, rtsp_client_incoming_cb, rtsp_sock, EV_READ);
	ev_io_start(rtsp_loop, io);

	return true;

open_error:
	close(rtsp_sock);
	return false;
}

int rtsp_bind_sockets()
{
	struct addrinfo *rtsp_addrinfo, *it;
	int ret;

	static const struct addrinfo hints_ipv4= {
		.ai_family= AF_INET, /* IPv4 ONLY */
		.ai_socktype= SOCK_STREAM,
		.ai_protocol = 0,
		.ai_flags= AI_PASSIVE
	};

	ret= getaddrinfo(ADDR_HOST, ADDR_PORT, &hints_ipv4, &rtsp_addrinfo);
	if(ret== -1){
		xlog(LOG_ERR, "get addrinfo error");
		exit(1);
	}
	char ip_print_buf[20];

	it= rtsp_addrinfo;
	do{
		struct sockaddr_in *sock_in_tmp= (struct sockaddr_in *)it->ai_addr;
		inet_ntop(AF_INET, &sock_in_tmp->sin_addr, ip_print_buf, 16);
		xlog(LOG_INF, "rtsp bind ip is %s", ip_print_buf);
		if(!rtsp_bind_addr(it)){
			goto error;
		}
	}while((it= it->ai_next)!= NULL);

	freeaddrinfo(rtsp_addrinfo);

	return;

error:
	xlog(LOG_ERR, "error!");
	freeaddrinfo(rtsp_addrinfo);
	exit(1);
}