#include <pthread.h>

#include <stdio.h>

#include <sys/param.h>

#include <sys/types.h>

#include <linux/types.h>	/* don't move this one ! */

#include <sys/socket.h>

#include <sys/un.h>

#include <sys/uio.h>

#include <unistd.h>

#include <string.h>

#include <signal.h>

#include <stdlib.h>

#include <sys/time.h>

#include <sys/resource.h>

#include <sys/stat.h>

#include <syslog.h>

#include <netdb.h>

#include <fcntl.h>

#include <termio.h>

#include <errno.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <stdarg.h>

#include <ctype.h>

#include <linux/netlink.h>

static ssize_t writen(int fd, unsigned char *ptr, size_t nbytes) {
 ssize_t nwritten;
 size_t nleft;

 nleft = nbytes;
 while (nleft > 0) {
  nwritten = write(fd, ptr, nleft);
  if (nwritten <= 0) return nwritten;
  nleft -= nwritten;
  ptr += nwritten;
 }
 return nbytes - nleft;
}
