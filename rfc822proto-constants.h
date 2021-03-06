/* Automatically-generated code, do not modify! */ 
#ifndef RFC822PROTO_CONSTANTS_H__ 
#define RFC822PROTO_CONSTANTS_H__ 

typedef enum RFC822_Protocol 
{
	RFC822_Protocol_Invalid,
	RFC822_Protocol_Unsupported, 
	RFC822_Protocol_RTSP10,
	RFC822_Protocol_RTSP_UnsupportedVersion, 
	RFC822_Protocol_HTTP10,
	RFC822_Protocol_HTTP11,
	RFC822_Protocol_HTTP_UnsupportedVersion,
} RFC822_Protocol; 

typedef enum RFC822_Header 
{
	RFC822_Header__Invalid,
	RFC822_Header__Unsupported, 
	RFC822_Header_Allow,
	RFC822_Header_Authorization,
	RFC822_Header_Bandwidth, 
	RFC822_Header_CSeq,
	RFC822_Header_Content_Base,
	RFC822_Header_Content_Length, 
	RFC822_Header_Content_Type,
	RFC822_Header_Date,
	RFC822_Header_Location, 
	RFC822_Header_Proxy_Require,
	RFC822_Header_Public,
	RFC822_Header_RTP_Info, 
	RFC822_Header_Range,
	RFC822_Header_Referer,
	RFC822_Header_Require, 
	RFC822_Header_Server,
	RFC822_Header_Session,
	RFC822_Header_Speed, 
	RFC822_Header_Timestamp,
	RFC822_Header_Transport,
	RFC822_Header_Unsupported, 
	RFC822_Header_User_Agent,
	RFC822_Header_Cache_Control,
	RFC822_Header_Connection, 
	RFC822_Header_Expires,
	RFC822_Header_Pragma,
	RFC822_Header_x_sessioncookie,
}RFC822_Header;

typedef enum RTSP_Method
{ 
	RTSP_Method__Invalid, 
	RTSP_Method__Unsupported,
	RTSP_Method_DESCRIBE,
	RTSP_Method_OPTIONS, 
	RTSP_Method_PAUSE,
	RTSP_Method_PLAY,
	RTSP_Method_SETUP,
	RTSP_Method_TEARDOWN,
}RTSP_Method;

typedef enum RTSP_Header
{
	RTSP_Header__Invalid, 
	RTSP_Header__Unsupported,
	RTSP_Header_Allow = RFC822_Header_Allow, 
	RTSP_Header_Authorization = RFC822_Header_Authorization,
	RTSP_Header_Bandwidth = RFC822_Header_Bandwidth,
	RTSP_Header_CSeq = RFC822_Header_CSeq, 
	RTSP_Header_Content_Base = RFC822_Header_Content_Base, 
	RTSP_Header_Content_Length = RFC822_Header_Content_Length, 
	RTSP_Header_Content_Type = RFC822_Header_Content_Type,
	RTSP_Header_Date = RFC822_Header_Date,
	RTSP_Header_Location = RFC822_Header_Location, 
	RTSP_Header_Proxy_Require = RFC822_Header_Proxy_Require,
	RTSP_Header_Public = RFC822_Header_Public,
	RTSP_Header_RTP_Info = RFC822_Header_RTP_Info, 
	RTSP_Header_Range = RFC822_Header_Range,
	RTSP_Header_Referer = RFC822_Header_Referer,
	RTSP_Header_Require = RFC822_Header_Require, 
	RTSP_Header_Server = RFC822_Header_Server,
	RTSP_Header_Session = RFC822_Header_Session,
	RTSP_Header_Speed = RFC822_Header_Speed, 
	RTSP_Header_Timestamp = RFC822_Header_Timestamp,
	RTSP_Header_Transport = RFC822_Header_Transport,
	RTSP_Header_Unsupported = RFC822_Header_Unsupported, 
	RTSP_Header_User_Agent = RFC822_Header_User_Agent,
}RTSP_Header;

typedef enum RTSP_ReponseCode
{
	RTSP_Continue = 100,
	RTSP_Ok = 200,
	RTSP_Created = 201, 
	RTSP_Accepted = 202,
	RTSP_Found = 302, 
	RTSP_BadRequest = 400, 
	RTSP_Forbidden = 403, 
	RTSP_NotFound = 404, 
	RTSP_NotAcceptable = 406, 
	RTSP_UnsupportedMediaType = 415, 
	RTSP_InternalServerError = 500, 
	RTSP_NotImplemented = 501, 
	RTSP_ServiceUnavailable = 503, 
	RTSP_VersionNotSupported = 505, 
	RTSP_ParameterNotUnderstood = 451, 
	RTSP_NotEnoughBandwidth = 453, 
	RTSP_SessionNotFound = 454, 
	RTSP_InvalidMethodInState = 455, 
	RTSP_HeaderFieldNotValidforResource = 456, 
	RTSP_InvalidRange = 457, 
	RTSP_AggregateNotAllowed = 459, 
	RTSP_AggregateOnly = 460, 
	RTSP_UnsupportedTransport = 461, 
	RTSP_OptionNotSupported = 551, 
} RTSP_ResponseCode; 

typedef enum HTTP_Method
{
	HTTP_Method__Invalid, 
	HTTP_Method__Unsupported, 
	HTTP_Method_GET, 
	HTTP_Method_POST,
}HTTP_Method; 

typedef enum HTTP_Header 
{ 
	HTTP_Header__Invalid, 
	HTTP_Header__Unsupported, 
	HTTP_Header_Cache_Control = RFC822_Header_Cache_Control, 
	HTTP_Header_Connection = RFC822_Header_Connection, 
	HTTP_Header_Content_Length = 
	RFC822_Header_Content_Length, 
	HTTP_Header_Content_Type = RFC822_Header_Content_Type, 
	HTTP_Header_Date = RFC822_Header_Date, 
	HTTP_Header_Expires = RFC822_Header_Expires, 
	HTTP_Header_Pragma = RFC822_Header_Pragma, 
	HTTP_Header_Server = RFC822_Header_Server, 
	HTTP_Header_User_Agent = RFC822_Header_User_Agent, 
	HTTP_Header_x_sessioncookie = 
	RFC822_Header_x_sessioncookie, 
} HTTP_Header; 

typedef enum HTTP_ReponseCode { 
	HTTP_Continue = 100, 
	HTTP_Ok = 200, 
	HTTP_Created = 201, 
	HTTP_Accepted = 202, 
	HTTP_Found = 302, 
	HTTP_BadRequest = 400, 
	HTTP_Forbidden = 403, 
	HTTP_NotFound = 404, 
	HTTP_NotAcceptable = 406, 
	HTTP_UnsupportedMediaType = 415, 
	HTTP_InternalServerError = 500, 
	HTTP_NotImplemented = 501, 
	HTTP_ServiceUnavailable = 503, 
	HTTP_VersionNotSupported = 505, 
} HTTP_ResponseCode; 

const char *rfc822_header_to_string(RFC822_Header hdr); 
const char *rfc822_response_reason(RFC822_Protocol proto, int code); 
const char *rfc822_proto_to_string(RFC822_Protocol proto);

#endif /*RFC822PROTO_CONSTANTS_H__ */ 