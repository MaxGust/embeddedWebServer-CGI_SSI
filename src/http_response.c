#include "http_response.h"
#include <stdio.h>
#include <string.h>

http_response_fileType_t http_response_getFileType(char *requestPath)
{
    char *fileType = strrchr(requestPath, '.');
    if (0 == fileType)
    {
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

    return -1;
}

http_response_contenttype_t http_response_get_contentType_string(http_response_fileType_t fileType, char *buffer, unsigned int bufferLength)
{
    if ((NULL == buffer) || (bufferLength <= 0))
    {
        return -1;
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
    return -1;
}
int http_response_response_header(const char *responseBody, http_response_code_t responseCode, char *headerBuffer, unsigned int bufferLength)
{
    if ((NULL == headerBuffer) || (bufferLength <= 0))
    {
        return -1;
    }

    if ((NULL == responseBody) && (responseCode))
    {
    }
    return -1;
}