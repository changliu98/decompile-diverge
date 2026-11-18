#include <unistd.h>

#include <stdlib.h>

#include <stdarg.h>

#include <stdio.h>

#include <string.h>

#include <syslog.h>

#include <limits.h>

#include <errno.h>

#include <ctype.h>

#include <fcntl.h>

#include <netdb.h>

#include <dirent.h>

#include <time.h>

#include <sys/param.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <sys/wait.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netinet/tcp.h>

#include <arpa/inet.h>

#include <getopt.h>

static char *strtoupper( char *s ){
 int i, len = sizeof(s);
 for( i = 0; i < len; i++ ){
  s[i] = ( s[i] >= 'a' && s[i] <= 'z' ? s[i] + 'A' - 'a' : s[i] );
 }
 return(s);
}
