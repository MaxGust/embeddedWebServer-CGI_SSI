#include "http_response.h"
#include "http_common.h"
#include "http_config.h"
#include <stdio.h>
#include <string.h>

http_response_fileType_t http_response_getFileType(char *requestPath)
{
    char *fileType;
    fileType = strrchr(requestPath, '.');
    if (0 == fileType)
    {
        PRINT_ERROR("File type  unknown\r\n");
        return HTTP_fileType_unknown;
    }

    fileType += 1;

    if (0 == strcmp(fileType, "shtml"))
        return HTTP_fileType_SHTML;
    else if (0 == strcmp(fileType, "shtm"))
        return HTTP_fileType_SHTM;
    else if (0 == strcmp(fileType, "ssi"))
        return HTTP_fileType_SSI;
    else if (0 == strcmp(fileType, "xml"))
        return HTTP_fileType_XML;
    else if (0 == strcmp(fileType, "cgi"))
        return HTTP_fileType_CGI;
    else if (0 == strcmp(fileType, "sh"))
        return HTTP_fileType_SH;
    else if (0 == strcmp(fileType, "exe"))
        return HTTP_fileType_EXE;
    else if (0 == strcmp(fileType, "html"))
        return HTTP_fileType_HTML;
    else if (0 == strcmp(fileType, "htm"))
        return HTTP_fileType_HTM;
    else if (0 == strcmp(fileType, "txt"))
        return HTTP_fileType_TXT;
    else if (0 == strcmp(fileType, "css"))
        return HTTP_fileType_CSS;
    else if (0 == strcmp(fileType, "js"))
        return HTTP_fileType_JS;
    else if (0 == strcmp(fileType, "json"))
        return HTTP_fileType_JSON;
    else if (0 == strcmp(fileType, "jpeg"))
        return HTTP_fileType_JPEG;
    else if (0 == strcmp(fileType, "jpg"))
        return HTTP_fileType_JPEG;
    else if (0 == strcmp(fileType, "png"))
        return HTTP_fileType_PNG;
    else if (0 == strcmp(fileType, "bin"))
        return HTTP_fileType_BIN;
    else if (0 == strcmp(fileType, "csv"))
        return HTTP_fileType_CSV;
    else if (0 == strcmp(fileType, "gif"))
        return HTTP_fileType_GIF;
    else if (0 == strcmp(fileType, "ico"))
        return HTTP_fileType_ICO;
    else if (0 == strcmp(fileType, "zip"))
        return HTTP_fileType_ZIP;
    else
        return HTTP_fileType_unknown;

    PRINT_ERROR("unhandled condition\r\n");
    return HTTP_FAILURE;
}

http_response_contenttype_t http_response_get_contentType_string(http_response_fileType_t fileType, char *buffer, unsigned int bufferLength)
{
    if ((NULL == buffer) || (bufferLength <= 0))
    {
        PRINT_ERROR("NULL buffer or zero length\r\n");
        return HTTP_FAILURE;
    }
    else
    {
        if ((fileType == HTTP_fileType_SHTML) || (fileType == HTTP_fileType_SHTM) ||
            (fileType == HTTP_fileType_SSI) || (fileType == HTTP_fileType_XML) ||
            (fileType == HTTP_fileType_SH) || (fileType == HTTP_fileType_EXE) ||
            (fileType == HTTP_fileType_HTML) || (fileType == HTTP_fileType_HTM) ||
            (fileType == HTTP_fileType_SHTM))
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_HTML, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_html;
        }
        else if (fileType == HTTP_fileType_TXT)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_PLAINTEXT, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_plaintext;
        }
        else if (fileType == HTTP_fileType_CSS)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_CSS, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_css;
        }
        else if (fileType == HTTP_fileType_JS)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_JS, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_js;
        }
        else if (fileType == HTTP_fileType_JSON)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_JSON, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_json;
        }
        else if (fileType == HTTP_fileType_JPEG)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_JPEG, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_jpeg;
        }
        else if (fileType == HTTP_fileType_PNG)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_PNG, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_png;
        }
        else if (fileType == HTTP_fileType_BIN)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_BIN, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_bin;
        }
        else if (fileType == HTTP_fileType_CSV)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_CSV, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_csv;
        }
        else if (fileType == HTTP_fileType_GIF)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_GIF, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_gif;
        }
        else if (fileType == HTTP_fileType_ICO)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_ICO, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_ico;
        }
        else if (fileType == HTTP_fileType_ZIP)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_ZIP, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_zip;
        }
        else if (fileType == HTTP_fileType_unknown)
        {
            strncpy(buffer, HTTP_RES_CONTENT_TYPE_PLAINTEXT, bufferLength);
            buffer[bufferLength] = 0;
            return HTTP_contentType_plaintext;
        }
    }

    PRINT_ERROR("unhandled condition\r\n");
    return HTTP_FAILURE;
}

int http_response_contentTypeToString(http_response_contenttype_t contentType, char *buffer, unsigned int length)
{
    if ((NULL == buffer) || (0 == length))
    {
        PRINT_ERROR("NULL buffer or 0 length");
        return HTTP_FAILURE;
    }

    switch (contentType)
    {
    case HTTP_contentType_unknown:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_PLAINTEXT, length);
        break;
    }
    case HTTP_contentType_plaintext:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_PLAINTEXT, length);
        break;
    }
    case HTTP_contentType_html:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_HTML, length);
        break;
    }
    case HTTP_contentType_css:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_CSS, length);
        break;
    }
    case HTTP_contentType_csv:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_CSV, length);
        break;
    }
    case HTTP_contentType_jpeg:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_JPEG, length);
        break;
    }
    case HTTP_contentType_png:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_PNG, length);
        break;
    }
    case HTTP_contentType_gif:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_GIF, length);
        break;
    }
    case HTTP_contentType_json:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_JSON, length);
        break;
    }
    case HTTP_contentType_js:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_JS, length);
        break;
    }
    case HTTP_contentType_zip:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_ZIP, length);
        break;
    }
    case HTTP_contentType_bin:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_BIN, length);
        break;
    }
    case HTTP_contentType_ico:
    {
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_ICO, length);
        break;
    }
    default:
    {
        PRINT_ERROR("unhandled case. passing default\r\n");
        strncpy(buffer, HTTP_RES_CONTENT_TYPE_PLAINTEXT, length);
    }
    }

    PRINT_ERROR("unhandled case\r\n");
    return HTTP_SUCCESS;
}

/*- responseBody can be NULL for responses that does not have a body
  - if transferEncoding is set to transferEnc_chunked , contentLength will be omitted from response.
    - so, budy need not be passed. 
  - either path or response contents type can be provided (both are optional , both can be null)
    - if path is provided, response content type will be computed from the extension and responseContentType argument is ignored
    - if path is null, response content type will be used. 
    - if response content type is also null, then no content type will be included in the response. 
*/

int http_response_response_header(HTTP_response_headerRequest_t headerRequest)
{
    if ((NULL == headerRequest.headerBuffer) || (headerRequest.bufferLength <= 0))
    {
        PRINT_ERROR(" null buffer or 0 length");
        return HTTP_FAILURE;
    }

    char responseLine[HTTP_RESPONSE_LINE1_LENGTH];
    char contentTypeLine[HTTP_RESPONSE_CONTTYPE_LENGTH];
    char contentLengthLine[HTTP_RESPONSE_CONLEN_LENGTH];
    char contentTypeLineDone = 0;
    char contentLengthLineDone = 0;

    responseLine[0]=0;
    contentTypeLine[0]=0;
    contentLengthLine[0]=0;
    headerRequest.headerBuffer[0]=0;

    //sprint response line 1
    //TODO: handle all responses
    switch (headerRequest.responseCode)
    {
    case HTTP_RESCODE_successSuccess: //200 OK
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_SUCCESS_SUCCESS);
        break;
    }
    case HTTP_RESCODE_successNocontent: //204
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_SUCCESS_NOCONTENT);
        break;
    }
    case HTTP_RESCODE_redirectNotmodified: //304
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_REDIRECT_NOTMODIFIED);
        break;
    }
    case HTTP_RESCODE_cerrorForbidden: // 403
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_CERROR_FORBIDDEN);
        break;
    }
    case HTTP_RESCODE_cerrorNotfound: // 401
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_CERROR_NOTFOUND);
        break;
    }
    case HTTP_RESCODE_cerrorPayloadlarge: //413
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_CERROR_PAYLOADLARGE);
        break;
    }
    case HTTP_RESCODE_cerrorUritoolong: //414
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_CERROR_URITOOLONG);
        break;
    }
    case HTTP_RESCODE_cerrorHeadertoolarge: ///431
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_CERROR_HEADERTOOLARGE);
        break;
    }
    case HTTP_RESCODE_serrorInternalerror: //500
    {
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_SERROR_INTERNALERROR);
        break;
    }
    default:
    {
        PRINT_ERROR("default case. passing default\r\n");
        snprintf(responseLine, HTTP_RESPONSE_LINE1_LENGTH, HTTP_RES_HTTP_VERSION " " HTTP_RESSTRING_SERROR_NOTIMPLEMENTED);
        break;
    }
    }

    //handle content type here
    if (NULL != headerRequest.filePath)
    {
        http_response_fileType_t fileType;
        char lcontentTypeLine[HTTP_RESPONSE_CONTTYPE_LENGTH];

        fileType = http_response_getFileType(headerRequest.filePath);
        int retval;
        retval = http_response_get_contentType_string(fileType, lcontentTypeLine, HTTP_RESPONSE_CONTTYPE_LENGTH);
        if (retval < 0)
        {
            PRINT_ERROR("error converting contentType to string\r\n");
        }
        snprintf(contentTypeLine, HTTP_RESPONSE_CONTTYPE_LENGTH, HTTP_RESHEADER_CONTENT_TYPE ": %s", lcontentTypeLine);
        contentTypeLineDone = 1;
    }
    else if (0 != headerRequest.contentType)
    {
        char lcontentTypeLine[HTTP_RESPONSE_CONTTYPE_LENGTH];
        int retVal;
        retVal = http_response_contentTypeToString(headerRequest.contentType, lcontentTypeLine, HTTP_RESPONSE_CONTTYPE_LENGTH);
        if (retVal < 0)
        {
            PRINT_ERROR("error converting contentType to string\r\n");
        }
        snprintf(contentTypeLine, HTTP_RESPONSE_CONTTYPE_LENGTH, HTTP_RESHEADER_CONTENT_TYPE ": %s", lcontentTypeLine);
        contentTypeLineDone = 1;
    }

    //handle content length and transfer encoding. 
    if (0 != headerRequest.bodyLength) //content length is applicable only when there is content
    {
        if (transferEnc_chunked == headerRequest.transferEncoding)
        {
            snprintf(contentLengthLine, HTTP_RESPONSE_CONLEN_LENGTH, HTTP_RESHEADER_TRANSFER_ENCODING ": chunked");
            contentLengthLineDone = 1;
        }
        else
        {
            snprintf(contentLengthLine, HTTP_RESPONSE_CONLEN_LENGTH, HTTP_RESHEADER_CONTENT_LENGTH ": %d", headerRequest.bodyLength);
            contentLengthLineDone = 1;
        }
    }

    //final Assembly
    if(headerRequest.bufferLength<(strlen(responseLine)+strlen(contentTypeLine)+strlen(contentLengthLine))){
        PRINT_ERROR("total header length > provided buffer\r\n");
        return HTTP_FAILURE;
    }

    int printedChar;
    printedChar = snprintf(headerRequest.headerBuffer, headerRequest.bufferLength, "%s\r\n", responseLine);
    if (0 != contentTypeLineDone)
    {
        headerRequest.bufferLength -= printedChar + 1;
        printedChar += snprintf((headerRequest.headerBuffer + printedChar), headerRequest.bufferLength, "%s\r\n", contentTypeLine);
    }
    if (0 != contentLengthLineDone)
    {
        headerRequest.bufferLength -= printedChar + 1;
        printedChar += snprintf((headerRequest.headerBuffer + printedChar), headerRequest.bufferLength, "%s\r\n", contentLengthLine);
    }

    snprintf((headerRequest.headerBuffer + printedChar), headerRequest.bufferLength, "\r\n");

    return HTTP_SUCCESS;
}