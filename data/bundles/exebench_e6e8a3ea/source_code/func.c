#include <sys/stat.h>

#include <sys/socket.h>

#include <sys/ioctl.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <netdb.h>

#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <string.h>

#include <unistd.h>

#include <syslog.h>

#include <stdarg.h>

#include <signal.h>

#include <arpa/inet.h>

#include <errno.h>

#include <ctype.h>

int last_slash(const char *path, int *number_found, int *path_size)
{
   int i, found=0, lasti=0;


   for (i=0; path[i] && i<256; i++)
      if (path[i] == '/')
      {
         found++;
         lasti=i;
      }

   *number_found = found;
   *path_size = i;

   return lasti;
}
