#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#define HTTP_RESPONSE_LINE1_LENGTH (unsigned int)50
#define HTTP_RESPONSE_CONTTYPE_LENGTH (unsigned int)50
#define HTTP_RESPONSE_CONLEN_LENGTH (unsigned int)50

/*response code mappings. Ref: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status
  These strings will sent back along with HTTP version and additional response headers. 
*/
#define HTTP_RESSTRING_INFO_CONTINUE "100 Continue"
#define HTTP_RESSTRING_INFO_SWITCHING "101 Switching Protocol"
//SUCCESS codes
#define HTTP_RESSTRING_SUCCESS_SUCCESS "200 OK"
#define HTTP_RESSTRING_SUCCESS_CREATED "201 Created"
#define HTTP_RESSTRING_SUCCESS_ACCEPTED "202 Accepted"
#define HTTP_RESSTRING_SUCCESS_NONAUTHO "203 Non-Authoritative Information"
#define HTTP_RESSTRING_SUCCESS_NOCONTENT "204 No Content"
#define HTTP_RESSTRING_SUCCESS_RESETCONTENT "205 Reset Content"
#define HTTP_RESSTRING_SUCCESS_PARTIAL "206 Partial Content"
//REDIRECT Codes
#define HTTP_RESSTRING_REDIRECT_MULTIPLE "300 Multiple Choice"
#define HTTP_RESSTRING_REDIRECT_MOVED "301 Moved Permanently"
#define HTTP_RESSTRING_REDIRECT_FOUND "302 Found"
#define HTTP_RESSTRING_REDIRECT_OTHER "303 See Other"
#define HTTP_RESSTRING_REDIRECT_NOTMODIFIED "304 Not Modified"
#define HTTP_RESSTRING_REDIRECT_TEMPREDIRECT "307 Temporary Redirect"
#define HTTP_RESSTRING_REDIRECT_PERMREDIRECT "308 Permanent Redirect"
//Client error codes
#define HTTP_RESSTRING_CERROR_BADREQ "400 Bad Request"
#define HTTP_RESSTRING_CERROR_UNAUTH "401 Unauthorized"
#define HTTP_RESSTRING_CERROR_FORBIDDEN "403 Forbidden"
#define HTTP_RESSTRING_CERROR_NOTFOUND "404 Not Found"
#define HTTP_RESSTRING_CERROR_NOTALLOWED "405 Method Not Allowed"
#define HTTP_RESSTRING_CERROR_NOTACCEPTABLE "406 Not Acceptable"
#define HTTP_RESSTRING_CERROR_PROXYAUTH "407 Proxy Authentication Required"
#define HTTP_RESSTRING_CERROR_TIMEOUT "408 Request Timeout"
#define HTTP_RESSTRING_CERROR_CONFLICT "409 Conflict"
#define HTTP_RESSTRING_CERROR_GONE "410 Gone"
#define HTTP_RESSTRING_CERROR_LENGTHREQUIRED "411 Length Required"
#define HTTP_RESSTRING_CERROR_PRECONDFAIL "412 Precondition Failed"
#define HTTP_RESSTRING_CERROR_PAYLOADLARGE "413 Payload Too Large"
#define HTTP_RESSTRING_CERROR_URITOOLONG "414 URI Too Long"
#define HTTP_RESSTRING_CERROR_UNSUPMEDIA "415 Unsupported Media Type"
#define HTTP_RESSTRING_CERROR_UNSUPREQRANGE "416 Requested Range Not Satisfiable"
#define HTTP_RESSTRING_CERROR_EXPECTATIONFAIL "417 Expectation Failed"
#define HTTP_RESSTRING_CERROR_IAMATEAPOT "418 I'm a teapot"
#define HTTP_RESSTRING_CERROR_UPGRADEREQUIRED "426 Upgrade Required"
#define HTTP_RESSTRING_CERROR_PRECONDREQD "428 Precondition Required"
#define HTTP_RESSTRING_CERROR_TOOMANYREQ "429 Too Many Requests"
#define HTTP_RESSTRING_CERROR_HEADERTOOLARGE "431 Request Header Fields Too Large"
#define HTTP_RESSTRING_CERROR_LEGALUNAVAIL "451 Unavailable For Legal Reasons"
//Server Error codes
#define HTTP_RESSTRING_SERROR_INTERNALERROR "500 Internal Server Error"
#define HTTP_RESSTRING_SERROR_NOTIMPLEMENTED "501 Not Implemented"
#define HTTP_RESSTRING_SERROR_BADGATEWAY "502 Bad Gateway"
#define HTTP_RESSTRING_SERROR_SERVICEUNAVIL "503 Service Unavailable"
#define HTTP_RESSTRING_SERROR_GATEWAYTIMEOUT "504 Gateway Timeout"
#define HTTP_RESSTRING_SERROR_HTTPVERERROR "505 HTTP Version Not Supported"
#define HTTP_RESSTRING_SERROR_NETAUTHREQD "511 Network Authentication Required"

//enum mapping of HTTP response codes. 
typedef enum {
    HTTP_RESCODE_infoContinue = 100,
    HTTP_RESCODE_infoSwitching = 101,
    HTTP_RESCODE_successSuccess = 200,
    HTTP_RESCODE_successCreated = 201,
    HTTP_RESCODE_successAccepted = 202,
    HTTP_RESCODE_successNonautho = 203,
    HTTP_RESCODE_successNocontent = 204,
    HTTP_RESCODE_successResetcontent = 205,
    HTTP_RESCODE_successPartial = 206,
    HTTP_RESCODE_redirectMultiple = 300,
    HTTP_RESCODE_redirectMoved = 301,
    HTTP_RESCODE_redirectFound = 302,
    HTTP_RESCODE_redirectOther = 303,
    HTTP_RESCODE_redirectNotmodified = 304,
    HTTP_RESCODE_redirectTempredirect = 307,
    HTTP_RESCODE_redirectPermredirect = 308,
    HTTP_RESCODE_cerrorBadreq = 400,
    HTTP_RESCODE_cerrorUnauth = 401,
    HTTP_RESCODE_cerrorForbidden = 403,
    HTTP_RESCODE_cerrorNotfound = 404,
    HTTP_RESCODE_cerrorNotallowed = 405,
    HTTP_RESCODE_cerrorNotacceptable = 406,
    HTTP_RESCODE_cerrorProxyauth = 407,
    HTTP_RESCODE_cerrorTimeout = 408,
    HTTP_RESCODE_cerrorConflict = 409,
    HTTP_RESCODE_cerrorGone = 410,
    HTTP_RESCODE_cerrorLengthrequired = 411,
    HTTP_RESCODE_cerrorPrecondfail = 412,
    HTTP_RESCODE_cerrorPayloadlarge = 413,
    HTTP_RESCODE_cerrorUritoolong = 414,
    HTTP_RESCODE_cerrorUnsupmedia = 415,
    HTTP_RESCODE_cerrorUnsupreqrange = 416,
    HTTP_RESCODE_cerrorExpectationfail = 417,
    HTTP_RESCODE_cerrorIamateapot = 418,
    HTTP_RESCODE_cerrorUpgraderequired = 426,
    HTTP_RESCODE_cerrorPrecondreqd = 428,
    HTTP_RESCODE_cerrorToomanyreq = 429,
    HTTP_RESCODE_cerrorHeadertoolarge = 431,
    HTTP_RESCODE_cerrorLegalunavail = 451,
    HTTP_RESCODE_serrorInternalerror = 500,
    HTTP_RESCODE_serrorNotimplemented = 501,
    HTTP_RESCODE_serrorBadgateway = 502,
    HTTP_RESCODE_serrorServiceunavil = 503,
    HTTP_RESCODE_serrorGatewaytimeout = 504,
    HTTP_RESCODE_serrorHttpvererror = 505,
    HTTP_RESCODE_serrorNetauthreqd = 511
} http_response_code_t;  

/*enum mapping of supported file types. When adding a new file type here, also modify 
    - http_response_getFileType() to map a file extension to teh new type
    - http_response_get_contentType_string() to map the new fileType to a mime content type
*/
typedef enum {
    HTTP_fileType_unknown = 0,
    HTTP_fileType_SHTML = 1,
    HTTP_fileType_TXT,
    HTTP_fileType_SHTM,
    HTTP_fileType_SSI,
    HTTP_fileType_XML,
    HTTP_fileType_CGI,
    HTTP_fileType_SH,
    HTTP_fileType_EXE,
    HTTP_fileType_HTML,
    HTTP_fileType_HTM,
    HTTP_fileType_CSS,
    HTTP_fileType_JS,
    HTTP_fileType_JSON,
    HTTP_fileType_JPEG,
    HTTP_fileType_PNG,
    HTTP_fileType_BIN,
    HTTP_fileType_CSV,
    HTTP_fileType_GIF,
    HTTP_fileType_ICO,
    HTTP_fileType_ZIP
} http_response_fileType_t;

/*enum holding current content types*/
typedef enum {
    HTTP_contentType_unknown = 0,
    HTTP_contentType_plaintext,
    HTTP_contentType_html,
    HTTP_contentType_css,
    HTTP_contentType_csv,
    HTTP_contentType_jpeg,
    HTTP_contentType_png,
    HTTP_contentType_gif,
    HTTP_contentType_json,
    HTTP_contentType_js,
    HTTP_contentType_zip,
    HTTP_contentType_bin,
    HTTP_contentType_ico
} http_response_contenttype_t;

//HTTP content type strings to map http_response_contenttype_t
#define HTTP_RES_CONTENT_TYPE_PLAINTEXT "text/plain"
#define HTTP_RES_CONTENT_TYPE_HTML "text/html"
#define HTTP_RES_CONTENT_TYPE_CSS "text/css"
#define HTTP_RES_CONTENT_TYPE_CSV "text/csv"
#define HTTP_RES_CONTENT_TYPE_JPEG "image/jpeg"
#define HTTP_RES_CONTENT_TYPE_PNG "image/png"
#define HTTP_RES_CONTENT_TYPE_GIF "image/gif"
#define HTTP_RES_CONTENT_TYPE_JSON "application/json"
#define HTTP_RES_CONTENT_TYPE_JS "application/javascript"
#define HTTP_RES_CONTENT_TYPE_ZIP "application/zip"
#define HTTP_RES_CONTENT_TYPE_BIN "application/octet-stream"
#define HTTP_RES_CONTENT_TYPE_ICO "image/x-icon"

//currently supported header strings
#define HTTP_RES_HTTP_VERSION "HTTP/1.1"
#define HTTP_RESHEADER_CONTENT_LENGTH "Content-Length"
#define HTTP_RESHEADER_CONTENT_TYPE "Content-Type"
#define HTTP_RESHEADER_TRANSFER_ENCODING "Transfer-Encoding"

//ref: https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Transfer-Encoding
typedef enum
{
    transferEnc_none=0,
    transferEnc_chunked=1,
    transferEnc_compress,
    transferEnc_deflate,
    transferEnc_gzip,
    transferEnc_identity
}HTTP_response_transferEncoding_t;

/*structure to process a request to form a response header. This is to be sent before request body.*/
typedef struct
{
    http_response_code_t responseCode;  //required response code. 
    unsigned int bodyLength;            //body length to added in content length. keep as 0 if using chunked encoding 
    char *headerBuffer;                 //buffer to populate the return header result 
    unsigned int bufferLength;          //length of the buffer being passed in. 
    HTTP_response_transferEncoding_t transferEncoding;      // transfer encoding to be used . currently supporting only chunked. 
    char *filePath;
    http_response_contenttype_t contentType;
} HTTP_response_headerRequest_t;

/*function to create a response header
    IN: 
        - responseBody    :  string buffer containing response to be sent out. can be NULL for responses without contents
        - responseCode    :  response_code_t typed response code to send back
        - headerBuffer    :  buffer to be used to pack response header
        - bufferLength    :  length of headerBuffer
        - transferEncoding : set to transferEnc_none at init. set to transferEnc_chunked for chunked encoding
    OUT: 
        HTTP_SUCCESS on success
        value <0 on failure
*/
int http_response_response_header(HTTP_response_headerRequest_t headerRequest);

/*function to map path to file type extension of type http_response_fileType_t*/
http_response_fileType_t http_response_getFileType(char *requestPath);

/*function to identify content type of a fileType using default mappings. */
http_response_contenttype_t http_response_get_contentType_string(http_response_fileType_t fileType, char *buffer, unsigned int bufferLength);

/*function to convert a content type to string*/
int http_response_contentTypeToString(http_response_contenttype_t contentType, char *buffer, unsigned int length);

#endif