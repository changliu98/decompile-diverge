#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <string.h>

int
sha_init(int *hash)
{
  hash[0]=0x67452301;
  hash[1]=0xefcdab89;
  hash[2]=0x98badcfe;
  hash[3]=0x10325476;
  hash[4]=0xc3d2e1f0;
  return 0;
}
