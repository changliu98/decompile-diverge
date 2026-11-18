#include <stdio.h>

#include <stdlib.h>

#include <stdarg.h>

#include <string.h>

#include <ctype.h>

#include <errno.h>

static int StrSafeCopy(char *dst, const char *src, int size)
{
 char *d = dst;
 const char *s = src;
 int n = size;

 if (n != 0 && --n != 0) {
  do {
   if ((*d++ = *s++) == 0)
    break;
  } while (--n != 0);
 }

 if (n == 0) {
  if (size != 0)
   *d = '\0';
  while (*s++)
   ;
 }

 return (s - src - 1);
}
