#include"test.h"

/*test callbacks to replace SSI string timerVal*/
int exec1_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("/CGI/exec1.cgi", CGIPath))
  {
    return -1;
  }
  strncpy(replacerBuffer, "exec1 Executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return (int)strlen("exec1 Executed");
}
int exec2_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("/bin/exec2.sh", CGIPath))
  {
    return -1;
  }
  strncpy(replacerBuffer, "exec2 Executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return (int)strlen("exec2 Executed");
}
int exec3_CGI_cb(const char *CGIPath, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("/exec3.exe", CGIPath))
  {
    return -1;
  }
  strncpy(replacerBuffer, "exec3 executed", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return (int)strlen("exec3 Executed");
}

/*unit test for CGI*/
int test_CGI_registration(void)
{
  char *cgiPath1 = "/CGI/exec1.cgi";
  char *cgiPath2 = "/bin/exec2.sh";
  char *cgiPath3 = "/exec3.exe";

  http_CGI_pathFunction_t *cgiPathHandle1;
  cgiPathHandle1 = http_CGI_register_pathFunction(cgiPath1, exec1_CGI_cb, HTTP_contentType_bin);
  if (NULL == cgiPathHandle1)
  {
    printf(FAIL "test_CGI(1)\r\n");
    return -1;
  }
  if (HTTP_contentType_bin != http_cgi_get_contentType(cgiPathHandle1))
  {
    printf(FAIL "test_CGI(cgiPathHandle1 content type)\r\n");
    return -1;
  }

#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  http_CGI_pathFunction_t *cgiPathHandle2;
  cgiPathHandle2 = http_CGI_register_pathFunction(cgiPath2, exec2_CGI_cb, HTTP_contentType_bin);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_CGI(2)");
    return -1;
  }
  if (HTTP_contentType_bin != http_cgi_get_contentType(cgiPathHandle2))
  {
    printf(FAIL "test_CGI(cgiPathHandle2 content type)\r\n");
    return -1;
  }

#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  http_CGI_pathFunction_t *cgiPathHandle3;
  cgiPathHandle3 = http_CGI_register_pathFunction(cgiPath3, exec3_CGI_cb, HTTP_contentType_json);
  if (NULL == cgiPathHandle3)
  {
    printf(FAIL "test_CGI(3)");
    return -1;
  }
  if (HTTP_contentType_json != http_cgi_get_contentType(cgiPathHandle3))
  {
    printf(FAIL "test_CGI(cgiPathHandle3 content type)\r\n");
    return -1;
  }
#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  http_CGI_deRegister_pathFunction(cgiPathHandle2);
#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  //multiple registrations of the same CB
  cgiPathHandle2 = http_CGI_register_pathFunction(cgiPath3, exec3_CGI_cb, HTTP_contentType_plaintext);
  if (NULL == cgiPathHandle2)
  {
    printf(FAIL "test_CGI(4)");
    return -1;
  }
  if (HTTP_contentType_plaintext != http_cgi_get_contentType(cgiPathHandle2))
  {
    printf(FAIL "test_CGI(cgiPathHandle2 [rereg] content type)\r\n");
    return -1;
  }
#ifdef tesst_printPathFunctionTable
  http_CGI_printPathFunctionTable();
#endif

  printf(PASS "test_CGI\r\n");
  return 0;
}

int test_CGI_exec(void)
{
  char stringArray[100];
  //try for exec of "/CGI/exec1.cgi"
  if (strlen("exec1 Executed") == http_CGI_exec_pathFunction("/CGI/exec1.cgi", (char *)&stringArray, sizeof(stringArray)))
  {
    if (0 != strcmp(stringArray, "exec1 Executed"))
    {
      printf(FAIL "test_CGI_exec(1)\r\n");
      return -1;
    }
  }

  //try for a non-existant SSI string
  if (http_CGI_exec_pathFunction("nonExistantVal", (char *)&stringArray, sizeof(stringArray)) >= 0)
  {
    printf(FAIL "test_CGI_exec(2)\r\n");
    return -1;
  }

  //deregister all replacers
  http_CGI_deRegister_all();

  printf(PASS "test_CGI_exec\r\n");
  return 0;
}