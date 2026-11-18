#include <inttypes.h>

#include <stddef.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>

char* strcpy(char* s1, const char* s2)
{
 int i = 0;
 do { s1[i] = s2[i]; }
  while (s2[i++] != '\0');
 return s1;
}
