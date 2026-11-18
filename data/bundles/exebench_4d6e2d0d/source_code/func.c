#include <stdio.h>

#include <string.h>

static char *str_cpy(char *dst, const char *src) {
 char *d = dst;
 while ((*dst++ = *src++) != '\0')
  ;
 return d;
}
