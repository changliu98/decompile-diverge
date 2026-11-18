#include <sys/cdefs.h>

#include <ctype.h>

#include <err.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

char *
substitute(char *string, char chold, char chnew)
{
 char *cp = string;

 if (cp)
  while (*cp) {
   if (*cp == chold) {
    *cp = chnew;
    break;
   }
   cp++;
  }
 return (string);
}
