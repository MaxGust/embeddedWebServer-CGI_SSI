#include "test.h"

int test_response_fileType(void)
{
  char *testPath1 = "/index.html";
  char *testPath2 = "/index.shtml";
  char *testPath3 = "/index.txt";
  char *testPath4 = "/index.shtm";
  char *testPath5 = "/index.ssi";
  char *testPath6 = "/index.css";
  char *testPath7 = "/index.js";
  char *testPath8 = "/index.json";
  char *testPath9 = "/index.jpeg";
  char *testPath10 = "/index.png";
  char *testPath11 = "/index.bin";
  char *testPath12 = "/index.csv";
  char *testPath13 = "/index.gif";
  char *testPath14 = "/index.ico";
  char *testPath15 = "/index.zip";
  char *testPath16 = "/index";

  http_response_fileType_t fileType;
  fileType = http_response_getFileType(testPath1);
  if (HTTP_fileType_HTML != fileType)
  {
    printf(FAIL "test_response_fileType(1)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath2);
  if (HTTP_fileType_SHTML != fileType)
  {
    printf(FAIL "test_response_fileType(2)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath3);
  if (HTTP_fileType_TXT != fileType)
  {
    printf(FAIL "test_response_fileType(3)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath4);
  if (HTTP_fileType_SHTM != fileType)
  {
    printf(FAIL "test_response_fileType(4)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath5);
  if (HTTP_fileType_SSI != fileType)
  {
    printf(FAIL "test_response_fileType(5)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath6);
  if (HTTP_fileType_CSS != fileType)
  {
    printf(FAIL "test_response_fileType(6)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath7);
  if (HTTP_fileType_JS != fileType)
  {
    printf(FAIL "test_response_fileType(7)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath8);
  if (HTTP_fileType_JSON != fileType)
  {
    printf(FAIL "test_response_fileType(8)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath9);
  if (HTTP_fileType_JPEG != fileType)
  {
    printf(FAIL "test_response_fileType(9)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath10);
  if (HTTP_fileType_PNG != fileType)
  {
    printf(FAIL "test_response_fileType(10)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath11);
  if (HTTP_fileType_BIN != fileType)
  {
    printf(FAIL "test_response_fileType(11)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath12);
  if (HTTP_fileType_CSV != fileType)
  {
    printf(FAIL "test_response_fileType(12)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath13);
  if (HTTP_fileType_GIF != fileType)
  {
    printf(FAIL "test_response_fileType(13)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath14);
  if (HTTP_fileType_ICO != fileType)
  {
    printf(FAIL "test_response_fileType(14)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath15);
  if (HTTP_fileType_ZIP != fileType)
  {
    printf(FAIL "test_response_fileType(15)\r\n");
    return -1;
  }

  fileType = http_response_getFileType(testPath16);
  if (HTTP_fileType_unknown != fileType)
  {
    printf(FAIL "test_response_fileType(16)\r\n");
    return -1;
  }

  printf(PASS "test_response_fileType\r\n");
  return 0;
}

int test_response_contentType(void)
{
  http_response_contenttype_t contentType;
  char buffer[100];

  contentType = http_response_get_contentType_string(HTTP_fileType_HTML, (char *)&buffer, 100);
  if (HTTP_contentType_html != contentType)
  {
    printf(FAIL "test_response_contentType(1)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_HTML, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(2)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_TXT, (char *)&buffer, 100);
  if (HTTP_contentType_plaintext != contentType)
  {
    printf(FAIL "test_response_contentType(3)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_PLAINTEXT, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(4)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_CSS, (char *)&buffer, 100);
  if (HTTP_contentType_css != contentType)
  {
    printf(FAIL "test_response_contentType(5)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_CSS, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(6)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_JS, (char *)&buffer, 100);
  if (HTTP_contentType_js != contentType)
  {
    printf(FAIL "test_response_contentType(7)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_JS, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(8)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_JSON, (char *)&buffer, 100);
  if (HTTP_contentType_json != contentType)
  {
    printf(FAIL "test_response_contentType(9)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_JSON, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(10)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_JPEG, (char *)&buffer, 100);
  if (HTTP_contentType_jpeg != contentType)
  {
    printf(FAIL "test_response_contentType(11)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_JPEG, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(12)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_PNG, (char *)&buffer, 100);
  if (HTTP_contentType_png != contentType)
  {
    printf(FAIL "test_response_contentType(13)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_PNG, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(14)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_BIN, (char *)&buffer, 100);
  if (HTTP_contentType_bin != contentType)
  {
    printf(FAIL "test_response_contentType(15)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_BIN, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(16)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_CSV, (char *)&buffer, 100);
  if (HTTP_contentType_csv != contentType)
  {
    printf(FAIL "test_response_contentType(17)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_CSV, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(18)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_GIF, (char *)&buffer, 100);
  if (HTTP_contentType_gif != contentType)
  {
    printf(FAIL "test_response_contentType(19)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_GIF, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(20)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_ICO, (char *)&buffer, 100);
  if (HTTP_contentType_ico != contentType)
  {
    printf(FAIL "test_response_contentType(21)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_ICO, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(22)\r\n");
    return -2;
  }

  contentType = http_response_get_contentType_string(HTTP_fileType_ZIP, (char *)&buffer, 100);
  if (HTTP_contentType_zip != contentType)
  {
    printf(FAIL "test_response_contentType(23)\r\n");
    return -1;
  }
  else if (0 != strcmp(HTTP_RES_CONTENT_TYPE_ZIP, (char *)&buffer))
  {
    printf(FAIL "test_response_contentType(24)\r\n");
    return -2;
  }

  printf(PASS "test_response_contentType\r\n");
  return 0;
}

int test_response_header(void)
{

  HTTP_response_headerRequest_t headerRequest;
  char headerBuffer[300];
  http_response_initReponseStruct(&headerRequest);
  headerRequest.responseCode = HTTP_RESCODE_successSuccess;
  headerRequest.bodyLength = 1024;
  headerRequest.headerBuffer = (char *)&headerBuffer;
  headerRequest.bufferLength = 300;
  headerRequest.transferEncoding = transferEnc_none;
  headerRequest.filePath = "/index.html";

  int retBufLen = 0;

  retBufLen = http_response_response_header(headerRequest);

  char *expectedResponse1 = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 1024\r\n\r\n";

  if (strlen(expectedResponse1) != (unsigned int)retBufLen)
  {
    printf(FAIL "test_response_header(response length missmatch (200 OK))\r\n");
    return -1;
  }

  if (0 != strcmp(headerBuffer, expectedResponse1))
  {
    printf("%s\r\n", headerBuffer);
    printf(FAIL "test_response_header(1)\r\n");
    return -1;
  }

  headerRequest.filePath = NULL;
  headerRequest.responseCode = HTTP_RESCODE_serrorInternalerror; //invalid with content. just for unit test
  headerRequest.contentType = HTTP_contentType_bin;
  retBufLen = http_response_response_header(headerRequest);
  char *expectedResponse2 = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: application/octet-stream\r\nContent-Length: 1024\r\n\r\n";
  if (strlen(expectedResponse2) != (unsigned int)retBufLen)
  {
    printf(FAIL "test_response_header(response length HTTP_RESCODE_cerrorNotfound (500 Internal Error))\r\n");
    return -1;
  }
  if (0 != strcmp(headerBuffer, expectedResponse2))
  {
    printf(FAIL "test_response_header(2)\r\n");
    return -1;
  }

  //test chunked encoding with a different response code
  headerRequest.transferEncoding = transferEnc_chunked;
  headerRequest.responseCode = HTTP_RESCODE_cerrorNotfound;
  retBufLen = http_response_response_header(headerRequest);
  char *expectedResponse3 = "HTTP/1.1 404 Not Found\r\nContent-Type: application/octet-stream\r\nTransfer-Encoding: chunked\r\n\r\n";

  if (strlen(expectedResponse3) != (unsigned int)retBufLen)
  {
    printf(FAIL "test_response_header(response length HTTP_RESCODE_cerrorNotfound)\r\n");
    return -1;
  }

  if (0 != strcmp(headerBuffer, expectedResponse3))
  {
    printf(FAIL "test_response_header(HTTP_RESCODE_cerrorNotfound)\r\n");
    return -1;
  }

  //test small input buffer
  headerRequest.bufferLength = 3;
  int retval = http_response_response_header(headerRequest);
  if (retval >= 0)
  {
    printf(FAIL "test_response_header(Short Buffer)\r\n");
    return -1;
  }

  // printf("\r\n%s",headerBuffer);
  printf(PASS "test_response_header\r\n");
  return 0;
}
