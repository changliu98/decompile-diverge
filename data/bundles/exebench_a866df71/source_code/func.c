#include <netdb.h>

#include <netinet/in.h>

#include <sys/socket.h>

static char* skip(char *s, char c) {
 while(*s != c && *s != '\0')
  s++;
 if(*s != '\0')
  *s++ = '\0';
 return s;
}
