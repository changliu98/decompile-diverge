#include <string.h>

#include <stdint.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <sys/mman.h>

#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>

#include <asm/fcntl.h>

static int enddata(char *buff, int p)
{
 int pageaddr, offset;

 offset = p & 63;
 pageaddr = p-offset;

 if (offset == 0)
  return 0;

 buff[pageaddr + 1] = offset - 1;
 p = pageaddr + 64;

 return p;
}
