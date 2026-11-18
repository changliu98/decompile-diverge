#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <string.h>

#include <sys/mman.h>

#include <unistd.h>

#include <sys/ioctl.h>

#include <errno.h>

void si_swapl( int *d )
{
  union {
    int i;
    unsigned char c[4];
  }u;
  unsigned char tmp;

  u.i = *d;
  tmp = u.c[0];
  u.c[0] = u.c[3];
  u.c[3] = tmp;

  tmp = u.c[1];
  u.c[1] = u.c[2];
  u.c[2] = tmp;

  *d = u.i;
}
