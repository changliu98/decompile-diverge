#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>

#include <stdarg.h>

#include <string.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <netinet/ether.h>

#include <arpa/inet.h>

#include <syslog.h>

unsigned int ether_hash(unsigned char *ea)
{
 register unsigned int hash = 0;
 int i;

 for (i = 0; i < ETHER_ADDR_LEN; i++)
  hash = ea[i] + (hash << 6) + (hash << 16) - hash;

 return hash;
}
