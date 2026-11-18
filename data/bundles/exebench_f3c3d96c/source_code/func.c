#include <assert.h>

#include <string.h>

#include <stdio.h>

#include <stddef.h>

static void
nist_increment_block(unsigned int* V)
{
 int i;
 unsigned int x;

 for (i = (((128) / 8) / sizeof(int)) - 1; i >= 0; --i) {
  x = ntohl(V[i]) + 1;
  V[i] = htonl(x);
  if (x)
   return;
 }
}
