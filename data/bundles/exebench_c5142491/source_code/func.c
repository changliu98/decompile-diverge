#include <stdio.h>

#include <sys/types.h>

#include <unistd.h>

#include <string.h>

#include <errno.h>

#include <stdlib.h>

#include <signal.h>

int read_data(int fd, unsigned char *buf, int size)
{
 int cur = 0;
 int ret;
 while (cur != size) {
  ret = read(fd, buf + cur, size - cur);
  if (ret <= 0)
   return -1;
  cur += ret;
 }

 return 0;
}
