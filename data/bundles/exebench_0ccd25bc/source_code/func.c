#include <stdio.h>

#include <string.h>

int unicoder_utf32_decode(unsigned int* result, unsigned char* p, unsigned int endianness)
{
 int i;
 unsigned int decoded;

 if(endianness != 2 && endianness != 1)
  return -4;

 if(p == NULL)
  return -1;

 if(result == NULL)
  return -1;

 decoded= 0;

 for(i= 0; i < 4; i++)
 {
  if(endianness == 2)
  {
   if(i > 0) decoded <<= 8;
   decoded |= *(p + i);
  }

  else
  {
   if(i > 0) decoded >>= 8;
   decoded |= (((unsigned int) *(p + i)) << 24);
  }
 }


 if(decoded > 0x10ffff)
  return -16;


 if(0xd800 <= decoded && decoded <= 0xdfff)
  return -16;

 *result= decoded;
 return 4;
}
