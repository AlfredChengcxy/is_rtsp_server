
/* Automatically-generated code, do not modify! */

//#include "config.h"
#include <glib.h>
#include "rfc822proto.h"

/* When building PIC code, avoid tables here */
#if __PIC__ && !defined(AVOID_TABLES)
# define AVOID_TABLES 1
#endif


#if !AVOID_TABLES
const char *rfc822_header_to_string(RFC822_Header hdr)
{
    static const char *const header_names[] = {
        [RTSP_Header_Allow] = "Allow",
        [RTSP_Header_Authorization] = "Authorization",
        [RTSP_Header_Bandwidth] = "Bandwidth",
        [RTSP_Header_CSeq] = "CSeq",
        [RTSP_Header_Content_Base] = "Content-Base",
        [RTSP_Header_Content_Length] = "Content-Length",
        [RTSP_Header_Content_Type] = "Content-Type",
        [RTSP_Header_Date] = "Date",
        [RTSP_Header_Location] = "Location",
        [RTSP_Header_Proxy_Require] = "Proxy-Require",
        [RTSP_Header_Public] = "Public",
        [RTSP_Header_RTP_Info] = "RTP-Info",
        [RTSP_Header_Range] = "Range",
        [RTSP_Header_Referer] = "Referer",
        [RTSP_Header_Require] = "Require",
        [RTSP_Header_Server] = "Server",
        [RTSP_Header_Session] = "Session",
        [RTSP_Header_Speed] = "Speed",
        [RTSP_Header_Timestamp] = "Timestamp",
        [RTSP_Header_Transport] = "Transport",
        [RTSP_Header_Unsupported] = "Unsupported",
        [RTSP_Header_User_Agent] = "User-Agent",
        [HTTP_Header_Cache_Control] = "Cache-Control",
        [HTTP_Header_Connection] = "Connection",
        [HTTP_Header_Expires] = "Expires",
        [HTTP_Header_Pragma] = "Pragma",
        [HTTP_Header_x_sessioncookie] = "x-sessioncookie",

        NULL
    };

    g_assert(hdr > 0 &&
             (size_t)hdr < sizeof(header_names)/sizeof(header_names[0]));

    return header_names[hdr];
}

const char *rtsp_response_reason(int code) {
    static const char *const responses[1000] = {
        [451] = "Parameter Not Understood",
        [453] = "Not Enough Bandwidth",
        [454] = "Session Not Found",
        [455] = "Method Not Valid In This State",
        [456] = "Header Field Not Valid for Resource",
        [457] = "Invalid Range",
        [459] = "Aggregate Operation Not Allowed",
        [460] = "Only Aggregate Operation Allowed",
        [461] = "Unsupported Transport",
        [551] = "Option Not Supported",

        [999] = NULL
    };

    return responses[code];
}
const char *http_response_reason(int code) {
    static const char *const responses[1000] = {

        [999] = NULL
    };

    return responses[code];
}

const char *rfc822_response_reason(RFC822_Protocol proto, int code)
{
    static const char *const responses[1000] = {
        [100] = "Continue",
        [200] = "Ok",
        [201] = "Created",
        [202] = "Accepted",
        [302] = "Found",
        [400] = "Bad Request",
        [403] = "Forbidden",
        [404] = "Not Found",
        [406] = "Not Acceptable",
        [415] = "Unsupported Media Type",
        [500] = "Internal Server Error",
        [501] = "Not Implemented",
        [503] = "Service Unavailable",
        [505] = "Protocol Version Not Supported",

        [999] = NULL
    };

    g_assert(100 <= code && code <= 999);

    if ( responses[code] != NULL )
        return responses[code];

    switch(proto)
    {
    case RFC822_Protocol_RTSP10:
    case RFC822_Protocol_RTSP_UnsupportedVersion:
        return rtsp_response_reason(code);    case RFC822_Protocol_HTTP10:
    case RFC822_Protocol_HTTP11:
    case RFC822_Protocol_HTTP_UnsupportedVersion:
        return http_response_reason(code);
    };

    g_assert_not_reached();
    return NULL;
}

#else /* AVOID_TABLES */

const char *rfc822_header_to_string(RFC822_Header hdr)
{
    switch(hdr) {
        case RTSP_Header_Allow: return "Allow";
        case RTSP_Header_Authorization: return "Authorization";
        case RTSP_Header_Bandwidth: return "Bandwidth";
        case RTSP_Header_CSeq: return "CSeq";
        case RTSP_Header_Content_Base: return "Content-Base";
        case RTSP_Header_Content_Length: return "Content-Length";
        case RTSP_Header_Content_Type: return "Content-Type";
        case RTSP_Header_Date: return "Date";
        case RTSP_Header_Location: return "Location";
        case RTSP_Header_Proxy_Require: return "Proxy-Require";
        case RTSP_Header_Public: return "Public";
        case RTSP_Header_RTP_Info: return "RTP-Info";
        case RTSP_Header_Range: return "Range";
        case RTSP_Header_Referer: return "Referer";
        case RTSP_Header_Require: return "Require";
        case RTSP_Header_Server: return "Server";
        case RTSP_Header_Session: return "Session";
        case RTSP_Header_Speed: return "Speed";
        case RTSP_Header_Timestamp: return "Timestamp";
        case RTSP_Header_Transport: return "Transport";
        case RTSP_Header_Unsupported: return "Unsupported";
        case RTSP_Header_User_Agent: return "User-Agent";
        case HTTP_Header_Cache_Control: return "Cache-Control";
        case HTTP_Header_Connection: return "Connection";
        case HTTP_Header_Expires: return "Expires";
        case HTTP_Header_Pragma: return "Pragma";
        case HTTP_Header_x_sessioncookie: return "x-sessioncookie";

        default: g_assert_not_reached();
    }

    return NULL;
}

const char *rtsp_response_reason(int code) {
    switch(code) {
        case 451: return "Parameter Not Understood";
        case 453: return "Not Enough Bandwidth";
        case 454: return "Session Not Found";
        case 455: return "Method Not Valid In This State";
        case 456: return "Header Field Not Valid for Resource";
        case 457: return "Invalid Range";
        case 459: return "Aggregate Operation Not Allowed";
        case 460: return "Only Aggregate Operation Allowed";
        case 461: return "Unsupported Transport";
        case 551: return "Option Not Supported";

        default: g_assert_not_reached();
    }

    return NULL;
}

const char *http_response_reason(int code) {
    switch(code) {

        default: g_assert_not_reached();
    }

    return NULL;
}


const char *rfc822_response_reason(RFC822_Protocol proto, int code)
{
    switch(code) {
        case 100: return "Continue";
        case 200: return "Ok";
        case 201: return "Created";
        case 202: return "Accepted";
        case 302: return "Found";
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 406: return "Not Acceptable";
        case 415: return "Unsupported Media Type";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 503: return "Service Unavailable";
        case 505: return "Protocol Version Not Supported";

    };

    switch(proto)
    {
    case RFC822_Protocol_RTSP10:
    case RFC822_Protocol_RTSP_UnsupportedVersion:
        return rtsp_response_reason(code);    case RFC822_Protocol_HTTP10:
    case RFC822_Protocol_HTTP11:
    case RFC822_Protocol_HTTP_UnsupportedVersion:
        return http_response_reason(code);
    };

    g_assert_not_reached();
    return NULL;
}
#endif /* AVOID_TABLES */

const char *rfc822_proto_to_string(RFC822_Protocol proto)
{
    switch(proto)
    {
    case RFC822_Protocol_RTSP10:
        return "RTSP/1.0";
    case RFC822_Protocol_RTSP_UnsupportedVersion:
        return "RTSP/1.0";
    case RFC822_Protocol_HTTP10:
        return "HTTP/1.0";
    case RFC822_Protocol_HTTP11:
        return "HTTP/1.1";
    case RFC822_Protocol_HTTP_UnsupportedVersion:
        return "HTTP/1.1";

    };

    g_assert_not_reached();
    return NULL;
}
