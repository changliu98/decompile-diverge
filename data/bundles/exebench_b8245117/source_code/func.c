#include <stdio.h>

#include <ctype.h>

#include <stdlib.h>

#include <time.h>

char* mystrcpy(char *dest, char *src) {
 char *temp = dest;
 while(*src)
  *dest++ = *src++;
 *dest = '\0';
 return temp;
}
