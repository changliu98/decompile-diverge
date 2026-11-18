#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <unistd.h>

#include <err.h>

#include <time.h>

#include <errno.h>

#include <utime.h>

void putoct(char *str, unsigned short val)
{
 char *cp;

 *(cp = &str[7]) = '\0';
 *--cp = ' ';
 *--cp = (val & 07) + '0';
 while (cp != str)
  *--cp = (val >>= 3) ? (val & 07) + '0' : ' ';
}
