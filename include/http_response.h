#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

/*response code mappings. Ref: https://developer.mozilla.org/en-US/docs/Web/HTTP/Status*/
#define HTTP_RESCODE_INFO_CONTINUE          100
#define HTTP_RESSTRING_INFO_CONTINUE        "Continue"
#define HTTP_RESCODE_INFO_SWITCHING         101
#define HTTP_RESSTRING_INFO_SWITCHING       "Switching Protocol"
//SUCCESS codes
#define HTTP_RESCODE_SUCCESS_SUCCESS        200
#define HTTP_RESSTRING_SUCCESS_SUCCESS      "OK"
#define HTTP_RESCODE_SUCCESS_CREATED        201
#define HTTP_RESSTRING_SUCCESS_CREATED      "Created"
#define HTTP_RESCODE_SUCCESS_ACCEPTED       202
#define HTTP_RESSTRING_SUCCESS_ACCEPTED     "Accepted"
#define HTTP_RESCODE_SUCCESS_NONAUTHO       203
#define HTTP_RESSTRING_SUCCESS_NONAUTHO     "Non-Authoritative Information"
#define HTTP_RESCODE_SUCCESS_NOCONTENT      204
#define HTTP_RESSTRING_SUCCESS_NOCONTENT    "No Content"
#define HTTP_RESCODE_SUCCESS_RESETCONTENT   205
#define HTTP_RESSTRING_SUCCESS_RESETCONTENT "Reset Content"
#define HTTP_RESCODE_SUCCESS_PARTIAL        206
#define HTTP_RESSTRING_SUCCESS_PARTIAL      "Partial Content"
//REDIRECT Codes
#define HTTP_RESCODE_REDIRECT_MULTIPLE       300      
#define HTTP_RESSTRING_REDIRECT_MULTIPLE     "Multiple Choice"      
#define HTTP_RESCODE_REDIRECT_MOVED          301
#define HTTP_RESSTRING_REDIRECT_MOVED        "Moved Permanently"
#define HTTP_RESCODE_REDIRECT_FOUND          302
#define HTTP_RESSTRING_REDIRECT_FOUND        "Found"
#define HTTP_RESCODE_REDIRECT_OTHER          303
#define HTTP_RESSTRING_REDIRECT_OTHER        "See Other"
#define HTTP_RESCODE_REDIRECT_NOTMODIFIED    304
#define HTTP_RESSTRING_REDIRECT_NOTMODIFIED  "Not Modified"
#define HTTP_RESCODE_REDIRECT_TEMPREDIRECT   307
#define HTTP_RESSTRING_REDIRECT_TEMPREDIRECT "Temporary Redirect"
#define HTTP_RESCODE_REDIRECT_PERMREDIRECT   308
#define HTTP_RESSTRING_REDIRECT_PERMREDIRECT "Permanent Redirect"
//Client error codes
#define HTTP_RESCODE_CERROR_BADREQ            400
#define HTTP_RESSTRING_CERROR_BADREQ          "Bad Request"
#define HTTP_RESCODE_CERROR_UNAUTH            401
#define HTTP_RESSTRING_CERROR_UNAUTH          "Unauthorized"
#define HTTP_RESCODE_CERROR_FORBIDDEN         403
#define HTTP_RESSTRING_CERROR_FORBIDDEN       "Forbidden"
#define HTTP_RESCODE_CERROR_NOTFOUND          404
#define HTTP_RESSTRING_CERROR_NOTFOUND        "Not Found"
#define HTTP_RESCODE_CERROR_NOTALLOWED        405
#define HTTP_RESSTRING_CERROR_NOTALLOWED      "Method Not Allowed"
#define HTTP_RESCODE_CERROR_NOTACCEPTABLE     406
#define HTTP_RESSTRING_CERROR_NOTACCEPTABLE   "Not Acceptable"
#define HTTP_RESCODE_CERROR_PROXYAUTH         407
#define HTTP_RESSTRING_CERROR_PROXYAUTH       "Proxy Authentication Required"
#define HTTP_RESCODE_CERROR_TIMEOUT           408
#define HTTP_RESSTRING_CERROR_TIMEOUT         "Request Timeout"
#define HTTP_RESCODE_CERROR_CONFLICT          409
#define HTTP_RESSTRING_CERROR_CONFLICT        "Conflict"
#define HTTP_RESCODE_CERROR_GONE              410
#define HTTP_RESSTRING_CERROR_GONE            "Gone"
#define HTTP_RESCODE_CERROR_LENGTHREQUIRED    411
#define HTTP_RESSTRING_CERROR_LENGTHREQUIRED  "Length Required"
#define HTTP_RESCODE_CERROR_PRECONDFAIL       412
#define HTTP_RESSTRING_CERROR_PRECONDFAIL     "Precondition Failed"
#define HTTP_RESCODE_CERROR_PAYLOADLARGE      413
#define HTTP_RESSTRING_CERROR_PAYLOADLARGE    "Payload Too Large"
#define HTTP_RESCODE_CERROR_URITOOLONG        414
#define HTTP_RESSTRING_CERROR_URITOOLONG      "URI Too Long"
#define HTTP_RESCODE_CERROR_UNSUPMEDIA        415
#define HTTP_RESSTRING_CERROR_UNSUPMEDIA      "Unsupported Media Type"
#define HTTP_RESCODE_CERROR_UNSUPREQRANGE     416
#define HTTP_RESSTRING_CERROR_UNSUPREQRANGE   "Requested Range Not Satisfiable"
#define HTTP_RESCODE_CERROR_EXPECTATIONFAIL   417
#define HTTP_RESSTRING_CERROR_EXPECTATIONFAIL "Expectation Failed"
#define HTTP_RESCODE_CERROR_IAMATEAPOT        418
#define HTTP_RESSTRING_CERROR_IAMATEAPOT      "I'm a teapot"
#define HTTP_RESCODE_CERROR_UPGRADEREQUIRED   426
#define HTTP_RESSTRING_CERROR_UPGRADEREQUIRED "Upgrade Required"
#define HTTP_RESCODE_CERROR_PRECONDREQD       428
#define HTTP_RESSTRING_CERROR_PRECONDREQD     "Precondition Required"
#define HTTP_RESCODE_CERROR_TOOMANYREQ        429
#define HTTP_RESSTRING_CERROR_TOOMANYREQ      "Too Many Requests"
#define HTTP_RESCODE_CERROR_HEADERTOOLARGE    431
#define HTTP_RESSTRING_CERROR_HEADERTOOLARGE  "Request Header Fields Too Large"
#define HTTP_RESCODE_CERROR_LEGALUNAVAIL      451
#define HTTP_RESSTRING_CERROR_LEGALUNAVAIL    "Unavailable For Legal Reasons"
//Server Error codes
#define HTTP_RESCODE_SERROR_INTERNALERROR    500
#define HTTP_RESSTRING_SERROR_INTERNALERROR  "Internal Server Error"
#define HTTP_RESCODE_SERROR_NOTIMPLEMENTED   501
#define HTTP_RESSTRING_SERROR_NOTIMPLEMENTED "Not Implemented"
#define HTTP_RESCODE_SERROR_BADGATEWAY       502
#define HTTP_RESSTRING_SERROR_BADGATEWAY     "Bad Gateway"
#define HTTP_RESCODE_SERROR_SERVICEUNAVIL    503
#define HTTP_RESSTRING_SERROR_SERVICEUNAVIL  "Service Unavailable"
#define HTTP_RESCODE_SERROR_GATEWAYTIMEOUT   504
#define HTTP_RESSTRING_SERROR_GATEWAYTIMEOUT "Gateway Timeout"
#define HTTP_RESCODE_SERROR_HTTPVERERROR     505
#define HTTP_RESSTRING_SERROR_HTTPVERERROR   "HTTP Version Not Supported"
#define HTTP_RESCODE_SERROR_NETAUTHREQD      511
#define HTTP_RESSTRING_SERROR_NETAUTHREQD    "Network Authentication Required"


typedef enum {
  HTTP_RESCODE_infoContinue           =  100,
  HTTP_RESCODE_infoSwitching          =  101,
  HTTP_RESCODE_successSuccess         =  200,
  HTTP_RESCODE_successCreated         =  201,
  HTTP_RESCODE_successAccepted        =  202,
  HTTP_RESCODE_successNonautho        =  203,
  HTTP_RESCODE_successNocontent       =  204,
  HTTP_RESCODE_successResetcontent    =  205,
  HTTP_RESCODE_successPartial         =  206,
  HTTP_RESCODE_redirectMultiple       =  300,      
  HTTP_RESCODE_redirectMoved          =  301,
  HTTP_RESCODE_redirectFound          =  302,
  HTTP_RESCODE_redirectOther          =  303,
  HTTP_RESCODE_redirectNotmodified    =  304,
  HTTP_RESCODE_redirectTempredirect   =  307,
  HTTP_RESCODE_redirectPermredirect   =  308,
  HTTP_RESCODE_cerrorBadreq           =  400,
  HTTP_RESCODE_cerrorUnauth           =  401,
  HTTP_RESCODE_cerrorForbidden        =  403,
  HTTP_RESCODE_cerrorNotfound         =  404,
  HTTP_RESCODE_cerrorNotallowed       =  405,
  HTTP_RESCODE_cerrorNotacceptable    =  406,
  HTTP_RESCODE_cerrorProxyauth        =  407,
  HTTP_RESCODE_cerrorTimeout          =  408,
  HTTP_RESCODE_cerrorConflict         =  409,
  HTTP_RESCODE_cerrorGone             =  410,
  HTTP_RESCODE_cerrorLengthrequired   =  411,
  HTTP_RESCODE_cerrorPrecondfail      =  412,
  HTTP_RESCODE_cerrorPayloadlarge     =  413,
  HTTP_RESCODE_cerrorUritoolong       =  414,
  HTTP_RESCODE_cerrorUnsupmedia       =  415,
  HTTP_RESCODE_cerrorUnsupreqrange    =  416,
  HTTP_RESCODE_cerrorExpectationfail  =  417,
  HTTP_RESCODE_cerrorIamateapot       =  418,
  HTTP_RESCODE_cerrorUpgraderequired  =  426,
  HTTP_RESCODE_cerrorPrecondreqd      =  428,
  HTTP_RESCODE_cerrorToomanyreq       =  429,
  HTTP_RESCODE_cerrorHeadertoolarge   =  431,
  HTTP_RESCODE_cerrorLegalunavail     =  451,
  HTTP_RESCODE_serrorInternalerror    =  500,
  HTTP_RESCODE_serrorNotimplemented   =  501,
  HTTP_RESCODE_serrorBadgateway       =  502,
  HTTP_RESCODE_serrorServiceunavil    =  503,
  HTTP_RESCODE_serrorGatewaytimeout   =  504,
  HTTP_RESCODE_serrorHttpvererror     =  505,
  HTTP_RESCODE_serrorNetauthreqd      =  511
}http_response_code_t;

typedef enum{
    HTTP_fileType_unknown=0,
    HTTP_fileType_SHTML=1,
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
}http_response_fileType_t;

typedef enum{
    HTTP_contentType_unknown=0,
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
}http_response_contenttype_t;

//HTTP content types. not makign these static string to avoid program memory size
#define HTTP_RES_CONTENT_TYPE_PLAINTEXT    "text/plain"
#define HTTP_RES_CONTENT_TYPE_HTML         "text/html"
#define HTTP_RES_CONTENT_TYPE_CSS          "text/css"
#define HTTP_RES_CONTENT_TYPE_CSV          "text/csv"
#define HTTP_RES_CONTENT_TYPE_JPEG         "image/jpeg"
#define HTTP_RES_CONTENT_TYPE_PNG          "image/png"
#define HTTP_RES_CONTENT_TYPE_GIF          "image/gif"
#define HTTP_RES_CONTENT_TYPE_JSON         "application/json"
#define HTTP_RES_CONTENT_TYPE_JS           "application/javascript"
#define HTTP_RES_CONTENT_TYPE_ZIP          "application/zip"
#define HTTP_RES_CONTENT_TYPE_BIN          "application/octet-stream"
#define HTTP_RES_CONTENT_TYPE_ICO          "image/x-icon"

//header strings
#define HTTP_RES_HTTP_VERSION              "HTTP/1.1"
#define HTTP_RESHEADER_CONTENT_LENGTH      "Content-Length"  
#define HTTP_RESHEADER_CONTENT_TYPE        "Content-Type"
#define HTTP_RESHEADER_TRANSFER_ENCODING   "Transfer-Encoding"

/*function to create a response header
    IN: 
        - responseBody   :  string buffer containing response to be sent out. can be NULL for responses without contents
        - responseCode   :  response_code_t typed response code to send back
        - headerBuffer   :  buffer to be used to pack response header
        - buffer length  :  length of headerBuffer
    OUT: 
        HTTP_SUCCESS on success
        value <0 on failure
*/
int http_response_response_header (const char* responseBody,http_response_code_t responseCode, char* headerbuffer, unsigned int bufferLength);

/*function to map path to file type extension of type http_response_fileType_t*/
http_response_fileType_t http_response_getFileType(char* requestPath);

http_response_contenttype_t http_response_get_contentType_string(http_response_fileType_t fileType, char *buffer, unsigned int bufferLength);

#endif