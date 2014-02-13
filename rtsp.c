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
#include "glib.h"
#include "cfgparser/cfgparser.h"

#define MAXLEN 1023

/**
 * @brief Version string to use to report feng's signature
 */
const char feng_signature[] = "v1.0.2";

struct ev_loop *rtsp_loop;

void accept_callback(struct ev_loop *loop, ev_io *w, int revents);
void recv_callback(struct ev_loop *loop, ev_io *w, int revents);
void write_callback(struct ev_loop *loop, ev_io *w, int revents);

void accept_callback(struct ev_loop *loop, ev_io *w, int revents)
{
	int newfd;
	struct sockaddr_in sin;
	socklen_t addrlen = sizeof(struct sockaddr);
	ev_io* accept_watcher=malloc(sizeof(ev_io));
	while ((newfd = accept(w->fd, (struct sockaddr *)&sin, &addrlen)) < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
			//these are transient, so don't log anything.
			continue;
		}
		else
		{
			xlog(LOG_ERR, "accept error.[%s]", strerror(errno));
			break;
		}
	}
	ev_io_init(accept_watcher,recv_callback,newfd,EV_READ);
	ev_io_start(loop,accept_watcher);
	xlog(LOG_ERR, "accept callback : fd :%d",accept_watcher->fd);
}

void recv_callback(struct ev_loop *loop, ev_io *w, int revents)
{
	char buffer[1024]={0};
	int ret =0;
	//ev_io write_event;
loop:
	ret=recv(w->fd,buffer,MAXLEN,0);
	if(ret > 0){
		xlog(LOG_ERR, "recv message :%s  ",buffer);
	}
	else if(ret ==0){
		xlog(LOG_ERR, "remote socket closed!socket fd: %d",w->fd);
		close(w->fd);
		ev_io_stop(loop, w);
		free(w);
		return;
	}
	else{
		if(errno == EAGAIN ||errno == EWOULDBLOCK){
			goto loop;
		}
		else{
			xlog(LOG_ERR, "ret :%d ,close socket fd : %d",ret,w->fd);
			close(w->fd);
			ev_io_stop(loop, w);
			free(w);
			return;
		}
	}
	int fd=w->fd;
	ev_io_stop(loop,  w);
	ev_io_init(w,write_callback,fd,EV_WRITE);
	ev_io_start(loop,w);
	xlog(LOG_ERR, "socket fd : %d, turn read 2 write loop! ",fd);

}

void write_callback(struct ev_loop *loop, ev_io *w, int revents)
{
	char buffer[1024]={0};
	//ev_io read_event;
	snprintf(buffer,1023,"this is a libev server!");
	write(w->fd,buffer,strlen(buffer),0);
	int fd=w->fd;
	ev_io_stop(loop,  w);
	ev_io_init(w,recv_callback,fd,EV_READ);
	ev_io_start(loop,w);
}

GList *configured_vhosts;
cfg_options_t feng_srv = {
    /* set default here for pre-initialisation logs */
    .log_level = LOG_WAR
};

static void fncheader()
{
//    printf("\n"PACKAGE" - Feng "VERSION"\n LScube Project - Politecnico di Torino\n");
    printf("\n"" - Feng version need to be added here." "\n LScube Project - Politecnico di Torino\n");
}

static gboolean show_version(ATTR_UNUSED const gchar *option_name,
                             ATTR_UNUSED const gchar *value,
                             ATTR_UNUSED gpointer data,
                             ATTR_UNUSED GError **error)
{
  fncheader();
  exit(0);
}

static void command_environment(int argc, char **argv)
{
#ifndef CLEANUP_DESTRUCTOR
    gchar *progname;
#endif
    gchar *config_file = NULL;
    gboolean quiet = FALSE, verbose = FALSE, lint = FALSE;

    GOptionEntry optionsTable[] = {
        { "config", 'f', 0, G_OPTION_ARG_STRING, &config_file,
            "specify configuration file", NULL },
        { "quiet", 'q', 0, G_OPTION_ARG_NONE, &quiet,
            "show as little output as possible", NULL },
        { "verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose,
            "output to standard error (debug)", NULL },
        { "version", 'V', G_OPTION_FLAG_NO_ARG, G_OPTION_ARG_CALLBACK, show_version,
            "print version information and exit", NULL },
        { "lint", 'l', 0, G_OPTION_ARG_NONE, &lint,
          "check the configuration file for errors, then exit", NULL },
        { NULL, 0, 0, 0, NULL, NULL, NULL }
    };

    GError *error = NULL;
    GOptionContext *context = g_option_context_new("");
    g_option_context_add_main_entries(context, optionsTable, "iskey.tar.gz");

    g_option_context_parse(context, &argc, &argv, &error);
    g_option_context_free(context);

    if ( error != NULL ) {
        xlog(LOG_FAT, "%s", error->message);
        exit(1);
    }

    if (!quiet && !lint) fncheader();

//    config_file_parse(config_file, lint);

    g_free(config_file);

    /* if we're doing a verbose run, make sure to output
       everything directly on standard error.
    */
    if ( verbose ) {
        feng_srv.log_level = LOG_INF;
        feng_srv.error_log = "stderr";
    }

    progname = g_path_get_basename(argv[0]);

//    fnc_log_init(progname);
}

cfg_vhost_t g_default_vhost;

void config_file_parse()
{
    g_default_vhost.document_root="/";

    g_default_vhost.access_log= "stderr";

    g_default_vhost.max_connections= 100;
}

int main(int argc ,char** argv)
{
    if(!g_thread_supported()) g_thread_init(NULL);

	int listen;

    command_environment(argc, argv);
    config_file_parse();//need to be added in command_environment

	rtsp_loop= ev_default_loop(0);
	rtsp_bind_sockets();

	clients_init();

	ev_loop(rtsp_loop, 0);
	// ev_io ev_io_watcher;
	// listen=socket_init();
	// struct ev_loop *loop = ev_loop_new(EVBACKEND_EPOLL);
	// ev_io_init(&ev_io_watcher, accept_callback,listen, EV_READ);
	// ev_io_start(loop,&ev_io_watcher);
	// ev_loop(loop,0);
	// ev_loop_destroy(loop);
	return 0;
}
