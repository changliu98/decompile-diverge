#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <errno.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <unistd.h>

#include <signal.h>

#include <limits.h>

int write_buff(int fd, unsigned char *data, ssize_t size)
{
 char *ptr = data;
 ssize_t n;
 ssize_t sz = size;

 while (sz > 0) {
  n = write(fd, ptr, sz);
  if (n < 0)
   return -1;
  sz -= n;
  ptr += n;
 }
 return size;
}
