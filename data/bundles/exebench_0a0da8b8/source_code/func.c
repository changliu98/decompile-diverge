#include <stdlib.h>

#include <string.h>

#include <ctype.h>

#include <stdio.h>

void string_reverse (char *s)
{
  char *t = s;

  while (*t != '\0') t++;
  while (s < t)
  {
    int c = *s;
    *s++ = *--t;
    *t = c;
  }
}
