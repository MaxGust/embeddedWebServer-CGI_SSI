#include"test.h"
/*test callbacks to replace SSI string timerVal*/
int timerVal_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("timerVal", SSIString))
  {
    printf(FAIL "timerVal_SSI_replacer_cb (SSI string missmatch)\r\n");
    return -1;
  }
  strncpy(replacerBuffer, "timerValue is 200", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int sysStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("sysStatus", SSIString))
  {
    printf(FAIL "sysStatus_SSI_replacer_cb (SSI string missmatch)\r\n");
    return -1;
  }
  strncpy(replacerBuffer, "System is up and running", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}
int resetStatus_SSI_replacer_cb(const char *SSIString, char *replacerBuffer, unsigned int bufferLength)
{
  if (0 != strcmp("resetStatus", SSIString))
  {
    printf(FAIL "resetStatus_SSI_replacer_cb (SSI string missmatch)\r\n");
    return -1;
  }
  strncpy(replacerBuffer, "Previous reset caused by Watchdog", bufferLength);
  replacerBuffer[bufferLength] = 0;
  return 0;
}

/*test routine to check if callback registration for SSI string is done properly*/
int test_SSIStringRegistration(void)
{
  char *testSSIString1 = "timerVal";
  char *testSSIString2 = "sysStatus";
  char *testSSIString3 = "resetStatus";

  http_SSI_replacer_t *SSIReplacementHandle1;
  SSIReplacementHandle1 = http_SSI_register_replacer(testSSIString1, timerVal_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle1)
  {
    printf(FAIL "test_SSIStringRegistration(http_SSI_register_replacer 1)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(http_SSI_register_replacer 1)\r\n");

#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  http_SSI_replacer_t *SSIReplacementHandle2;
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString2, sysStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf(FAIL "test_SSIStringRegistration(2)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(http_SSI_register_replacer 2)\r\n");
#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  http_SSI_replacer_t *SSIReplacementHandle3;
  SSIReplacementHandle3 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle3)
  {
    printf(FAIL "test_SSIStringRegistration(3)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(http_SSI_register_replacer 3)\r\n");

#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  http_SSI_deRegister_replacer(SSIReplacementHandle2);
#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  //multiple registrations of the same CB
  SSIReplacementHandle2 = http_SSI_register_replacer(testSSIString3, resetStatus_SSI_replacer_cb);
  if (NULL == SSIReplacementHandle2)
  {
    printf(FAIL "test_SSIStringRegistration(4)\r\n");
    return -1;
  }
  printf(PASS "test_SSIStringRegistration(register after deregister)\r\n");

#ifdef test_debugTablePrint
  http_SSI_printReplacerTable();
#endif

  printf(PASS ">>test_SSIStringRegistration<<\r\n");
  return 0;
}

/*unittest for replacement matching */
int test_SSIStringReplacementCB(void)
{
  char stringArray[100];
  //try for replacement string of "timerVal"
  if (0 == http_SSI_get_replacer_string("timerVal", (char *)&stringArray, sizeof(stringArray)))
  {
    if (0 != strcmp(stringArray, "timerValue is 200"))
    {
      printf(FAIL "test_SSIStringReplacementCB(1)\r\n");
      return -1;
    }
  }

  //try for a non-existant SSI string
  if (0 == http_SSI_get_replacer_string("nonExistantVal", (char *)&stringArray, sizeof(stringArray)))
  {
    printf(FAIL "test_SSIStringReplacementCB(2)\r\n");
    return -1;
  }

  //deregister all replacers
  http_SSI_deRegister_all();

  printf(PASS "test_SSIStringReplacementCB\r\n");
  return 0;
}
