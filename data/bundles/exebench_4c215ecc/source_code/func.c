#include <inttypes.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

#include <time.h>

#include <ctype.h>

#include <unistd.h>

#include <fcntl.h>

#include <signal.h>

static inline char *stpcpy0(char *dest, const char *src) {


  while(*src!=0)
    *dest++= *src++;
  *dest= 0;
  return dest;
  }
