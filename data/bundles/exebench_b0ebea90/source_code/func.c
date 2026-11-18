#include <dlfcn.h>

#include <stdarg.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <fcntl.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <linux/dvb/ca.h>

#include <linux/dvb/dmx.h>

#include <linux/dvb/frontend.h>

#include <linux/ioctl.h>

#include <stdio.h>

#include <time.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

#include <sys/un.h>

#include <syslog.h>

#include <errno.h>

int sendcw(int fd, unsigned char *buff) {
  ;
  if ( send(fd,buff, 18, 0) == -1 ) {
   {syslog(LOG_ERR, "ca.so: Send cw failed %d", errno);};
    return 0;
  }
  return 1;
}
