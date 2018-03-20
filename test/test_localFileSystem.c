/**MIT License

Copyright (c) 2018 Vysakh P Pillai

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#include "test.h"

//copy of index contents in new file for test
static unsigned char index1_html[] = {
    0x3c, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x62, 0x6f,
    0x64, 0x79, 0x3e, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x48, 0x31, 0x3e,
    0x48, 0x45, 0x4c, 0x4c, 0x4f, 0x20, 0x57, 0x4f, 0x52, 0x4c, 0x44, 0x3c,
    0x2f, 0x48, 0x31, 0x3e, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x62, 0x6f, 0x64,
    0x79, 0x3e, 0x0a, 0x3c, 0x2f, 0x68, 0x74, 0x6d, 0x6c, 0x3e, 0x0a};
static unsigned int index1_html_len = 59;
static char *path_index1_html = "/index1.html";

int test_file_local_filesystem(void)
{
  http_localfs_init();
  http_localfs_filesystem_fp_t fp;

  //register default index file into the local file system.
  int retval = http_localfs_registerFile(path_index1_html, (char *)&index1_html, index1_html_len, 0);
  if (retval < 0)
  {
    printf(FAIL "test_file_local_filesystem(registerFile failed)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(rgister File)\r\n");
  //test fopen
  fp = http_localfs_fopen(path_index1_html);
  if (NULL == fp)
  {
    printf(FAIL "test_file_local_filesystem(fopen index)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fopen index)\r\n");

  //test content length using feof
  unsigned int i = 1;
  while (-1 != http_localfs_feof(fp))
  {
    http_localfs_fgetc(fp);
    i++;
  }
  if (index1_html_len != i)
  { //hard coded length of index file
    printf(FAIL "test_file_local_filesystem(content length(%d!=%d))\r\n", index1_html_len, i);
    return -1;
  }
  printf(PASS "test_file_local_filesystem(content Length)\r\n");
  http_localfs_fclose(fp);

  //test contents
  unsigned char fileContents[index1_html_len];
  fp = http_localfs_fopen(path_index1_html);
  i = 0;
  while (-1 != http_localfs_feof(fp))
  {
    fileContents[i] = (unsigned char)http_localfs_fgetc(fp);
    i++;
  }
  if (0 != strncmp((const char *)index1_html, (const char *)fileContents, index1_html_len - 1))
  {
    printf(FAIL "test_file_local_filesystem(content comparison)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(getc- content comparison)\r\n");

  http_localfs_fclose(fp);

  //fread test
  fp = http_localfs_fopen(path_index1_html);
  char fileReadBuffer[500];
  int readLength = http_localfs_fread((void *)&fileReadBuffer, 55, 1, fp);
  if (55 != readLength)
  {
    printf(FAIL "test_file_local_filesystem(read- length missmatch)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(read- lengthmissmatch)\r\n");
  if (0 != strncmp((const char *)index1_html, (const char *)fileReadBuffer, 55))
  {
    printf(FAIL "test_file_local_filesystem(read content comparison)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(read- content comparison)\r\n");

  //ty rto read more contents than remaining
  readLength = http_localfs_fread((void *)&fileReadBuffer, 100, 1, fp);
  if ((unsigned int)readLength != index1_html_len - 55)
  {
    printf(FAIL "test_file_local_filesystem(remaining read content length (%d,%d))\r\n", readLength, index1_html_len - 55);
    return -1;
  }
  printf(PASS "test_file_local_filesystem(remaining read content length (%d,%d))\r\n", readLength, index1_html_len - 55);
  //test remaining read contents
  if (0 != strncmp((const char *)&index1_html[55], (const char *)fileReadBuffer, readLength))
  {
    printf("%.*s\r\n", readLength, &index1_html[55]);
    printf("%.*s\r\n", readLength, fileReadBuffer);
    printf(FAIL "test_file_local_filesystem(remaining read content comparison(%d))\r\n", readLength);
    return -1;
  }
  printf(PASS "test_file_local_filesystem(remaining read content comparison(%d))\r\n", readLength);

  //try to read contents when it is already at EOF
  readLength = http_localfs_fread((void *)&fileReadBuffer, 100, 1, fp);
  if (-1 != readLength)
  {
    printf(FAIL "test_file_local_filesystem(over read test failure)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(read - over read test)\r\n");
  http_localfs_fclose(fp);

  fp = http_localfs_fopen(path_index1_html);
  int retVal = http_localfs_fseek(fp, 10, SEEK_SET);
  if ((0 != retVal) || (10 != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek SEEK_SET)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek offset SEEK_SET)\r\n");

  //test long seek set
  retVal = http_localfs_fseek(fp, 100, SEEK_SET);
  if ((0 != retVal) || ((index1_html_len - 1) != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek long SEEK_SET)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek long SEEK_SET)\r\n");

  //test seek end
  retVal = http_localfs_fseek(fp, -57, SEEK_END);
  if ((0 != retVal) || (1 != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek SEEK_END)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek SEEK_END)\r\n");

  //test seek end
  retVal = http_localfs_fseek(fp, -57, SEEK_END);
  if ((0 != retVal) || (0 != fp->filePosition))
  {
    printf(FAIL "test_file_local_filesystem(fseek long SEEK_END)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fseek long SEEK_END)\r\n");

  //test to open nonexistant file
  fp = http_localfs_fopen("/jibberish");
  if (NULL != fp)
  {
    printf(FAIL "test_file_local_filesystem(fopen Jibberish)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fopen - jibberish)\r\n");

  //test to close null FP
  if (HTTP_SUCCESS == http_localfs_fclose(fp))
  {
    printf(FAIL "test_file_local_filesystem(fclose Jibberish)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fclose - jibberish)\r\n");

  //deinit the filesystem
  if (HTTP_SUCCESS != http_localfs_deinit())
  {
    printf(FAIL "test_file_local_filesystem(fs deinit)\r\n");
    return -1;
  }
  printf(PASS "test_file_local_filesystem(fs deinit)\r\n");

  printf(PASS ">>test_file_local_filesystem<<\r\n");
  return 0;
}
