#include <stdio.h>

#include <stdarg.h>

#include <string.h>

#include <string.h>

#include <string.h>

#include <ctype.h>

#include <string.h>

#include <stdint.h>

#include <stdarg.h>

#include <string.h>

#include <ctype.h>

char *
strichr(char *p, int c)
{
 char *t;

 if (p != NULL) {
  for(t = p; *t; t++);
  for (; t >= p; t--) {
   *(t + 1) = *t;
  }
  *p = c;
 }
 return (p);
}
