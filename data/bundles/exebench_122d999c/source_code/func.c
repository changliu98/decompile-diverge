#include <stdio.h>

#include <ctype.h>

#include <stdlib.h>

#include <time.h>

char* mystpcpy(char *dest, char *src) {
 while(*src)
  *dest++ = *src++;
 *dest = '\0';
 return dest;
}
