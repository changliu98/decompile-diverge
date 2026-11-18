#include <string.h>

char* strset(char* str, int c)
{
  char* s = str;
  while (*s)
    *s++ = (char)c;
  return str;
}
