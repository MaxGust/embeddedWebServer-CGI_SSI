/*File to hold generic helper functions
  URL parser is from the website: https://rosettacode.org/wiki/URL_decoding
*/

#include <stdio.h>
#include <string.h>
#include "helperFunctions.h"
#include "http_config.h"
#include "http_common.h"

// for URL decoding function
static inline int ishex(int x)
{
  return (x >= '0' && x <= '9') ||
         (x >= 'a' && x <= 'f') ||
         (x >= 'A' && x <= 'F');
}

//URL decoding function
int url_decode(const char *s, char *dec)
{
  char *o;
  const char *end = s + strlen(s);
  int c;

  for (o = dec; s <= end; o++)
  {
    c = *s++;
    if (c == '+')
      c = ' ';
    else if (c == '%' && (!ishex(*s++) ||
                          !ishex(*s++) ||
                          !sscanf(s - 2, "%2x", &c)))
      return -1;

    if (dec)
      *o = c;
  }

  return o - dec;
}
