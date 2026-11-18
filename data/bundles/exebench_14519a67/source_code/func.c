#include <ctype.h>

#include <stddef.h>

#include <stdint.h>

#include <string.h>

char* strcpy(char *dest, const char *src)
{
 char *d = dest;
 while (*src)
  *d++ = *src++;

 *d = 0;
 return dest;
}
