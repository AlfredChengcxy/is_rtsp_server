#ifndef __X__LOG__
#define __X__LOG__

#ifdef __cplusplus
extern "C" {
#endif

#include "stdarg.h"
#include <stdio.h>

#define ENABLE_BLOG_FORCE 0

#define BLOG_STR_(a,b,c) a#b#c
#define BLOG_STR(a,b) a b"\n"

#define LOG_NOW LOG_DBG
#define LOG_DBG	20
#define LOG_INF	40
#define LOG_NOT	60
#define LOG_WAR	80
#define	LOG_ERR 100
#define LOG_FAT	120

#if (LOG_NOW<=LOG_FAT)
    #define _LOG_FAT(format,...) fprintf(stderr, BLOG_STR("LOG_FAT: FILE:%s, %s():%d,",format), __FILE__,__func__,__LINE__,##__VA_ARGS__);
#else
    #define _LOG_FAT(format,...)
#endif
#if (LOG_NOW<=LOG_ERR)
    #define _LOG_ERR(format,...) fprintf(stderr, BLOG_STR("LOG_ERR: FILE:%s, %s():%d,",format), __FILE__,__func__,__LINE__,##__VA_ARGS__);
#else
    #define _LOG_ERR(format,...)
#endif
#if (LOG_NOW<=LOG_INF)
    #define _LOG_INF(format,...) fprintf(stderr, BLOG_STR("LOG_INF: FILE:%s, %s():%d,",format), __FILE__,__func__,__LINE__,##__VA_ARGS__);
#else
    #define _LOG_INF(format,...)
#endif
#if LOG_NOW<=LOG_WAR
    #define _LOG_WAR(format,...) fprintf(stderr, BLOG_STR("LOG_WAR: FILE:%s, %s():%d,",format), __FILE__,__func__,__LINE__,##__VA_ARGS__);
#else
    #define _LOG_WAR(format,...)
#endif
#if LOG_NOW<=LOG_DBG
    #define _LOG_DBG(format,...) fprintf(stderr, BLOG_STR("LOG_DBG: FILE:%s, %s():%d,",format), __FILE__,__func__,__LINE__,##__VA_ARGS__);
#else
    #define _LOG_DBG(format,...)
#endif
#if LOG_NOW<=LOG_NOT
//    #define _LOG_NOT(format,...) fprintf(stderr, BLOG_STR("LOG_NOT: FILE:%s, %s():%d, %s:%s,",format), __FILE__,__func__,__LINE__, __DATE__,__TIME__,##__VA_ARGS__);
    #define _LOG_NOT(format,...) fprintf(stderr, BLOG_STR("LOG_NOT: FILE:%s, %s():%d,",format), __FILE__,__func__,__LINE__,##__VA_ARGS__);
#else
    #define _LOG_NOT(format,...)
#endif
	#define xlog(level, format, ...) _##level(format, ##__VA_ARGS__);
    #define xlog_init(conf) fprintf(stderr, "bnc_log init works at simple module.\n");
    #define xlog_fini() fprintf(stderr, "bnc_log fini works at simple module.\n");

#if ENABLE_BLOG_FORCE
    #undef printf
    #define printf please_use_bnc_log_instead_of_printf
#endif

#ifdef __cplusplus
}
#endif

#endif
