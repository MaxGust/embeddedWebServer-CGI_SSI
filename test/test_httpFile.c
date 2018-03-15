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


/*wrapper functions for type sanity. 
if this is not done casting fp to void will cause compiler warnings
*/
static void *http_localfs_fopen_w(const char *filename);
static int http_localfs_fclose_w(void *fp);
static size_t http_localfs_fread_w(void *ptr, size_t size, size_t nmemb, void *fp);
static int http_localfs_fgetc_w(void *fp);
static int http_localfs_fseek_w(void *fp, long offset, int whence);
static int http_localfs_feof_w(void *fp);

static void *http_localfs_fopen_w(const char *filename) { return (void *)http_localfs_fopen(filename); }
static int http_localfs_fclose_w(void *fp) { return http_localfs_fclose((http_localfs_filesystem_fp_t)fp); }
static size_t http_localfs_fread_w(void *ptr, size_t size, size_t nmemb, void *fp) { return http_localfs_fread(ptr, size, nmemb, (http_localfs_filesystem_fp_t)fp); }
static int http_localfs_fgetc_w(void *fp) { return http_localfs_fgetc((http_localfs_filesystem_fp_t)fp); }
static int http_localfs_fseek_w(void *fp, long offset, int whence) { return http_localfs_fseek((http_localfs_filesystem_fp_t)fp, offset, whence); }
static int http_localfs_feof_w(void *fp) { return http_localfs_feof((http_localfs_filesystem_fp_t)fp); }

int test_http_file(void)
{
  http_file_fops_t localFSFops;
  //init all to null

  http_localfs_deinit(); //just in case previous test left it in stale state
  http_localfs_init();

  //register default index file into the local file system.
  int retval = http_localfs_registerFile(path_index1_html, (char *)&index1_html, index1_html_len, 0);
  if (retval < 0)
  {
    printf(FAIL "test_http_file(registerFile failed)\r\n");
  }
  printf(PASS "test_http_file(rgister File)\r\n");

  http_file_init_fopsStruct(&localFSFops);
  printf(PASS "test_http_file(init fops struct fops)\r\n");
  localFSFops.fopen = http_localfs_fopen_w;
  localFSFops.fclose = http_localfs_fclose_w;
  localFSFops.fread = http_localfs_fread_w;
  localFSFops.fgetc = http_localfs_fgetc_w;
  localFSFops.fseek = http_localfs_fseek_w;
  localFSFops.feof = http_localfs_feof_w;

  http_file_register_fops(localFSFops);
  printf(PASS "test_http_file(register fops)\r\n");

  //now try calling the fops via the master http_file_fops
  void *fp = http_file_fops.fopen(path_index1_html);
  if (NULL == fp)
  {
    printf(FAIL "test_http_file(fopen index)\r\n");
    return -1;
  }
  printf(PASS "test_http_file(fopen index)\r\n");

  if (0 != http_file_fops.fclose(fp))
  {
    printf(FAIL "test_http_file(fclose index)\r\n");
    return -1;
  }
  printf(PASS "test_http_file(fclose index)\r\n");

  printf(PASS ">>test_http_file<<\r\n");
  return 0;
}
