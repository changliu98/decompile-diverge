#include <ctype.h>

#include <time.h>

#include <stdlib.h>

#include <stdio.h>

#include <stdarg.h>

#include <string.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <arpa/inet.h>

char *
mystpcpy(char *to, const char *from)
{
 for (; (*to = *from); ++from, ++to);
 return(to);
}
