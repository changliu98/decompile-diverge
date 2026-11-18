#include <arpa/inet.h>

#include <ctype.h>

#include <errno.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <sys/stat.h>

#include <time.h>

#include <sys/types.h>

#include <netinet/in.h>

#include <sys/socket.h>

#include <netdb.h>

#include <unistd.h>

char *
char_replace (char *str, char o, char n)
{
   if (str == NULL || *str == '\0')
      return str;

   char *p = str;
   while ((p = strchr (p, o)) != NULL)
      *p++ = n;

   return str;
}
