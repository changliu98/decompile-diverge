#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <dlfcn.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

void itoa(unsigned long i, char *b)
{
 unsigned long shifter = i;
 char *p = b;
 do {
  ++p;
  shifter = shifter/10;
 } while (shifter);
 *p = '\0';
 do {
  *--p = '0' + i%10;
  i = i/10;
 } while (i);
}
