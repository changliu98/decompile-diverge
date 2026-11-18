#include <stdio.h>

#include <string.h>

int unicoder_utf16_decode(unsigned int* result, unsigned char* p, unsigned int endianness)
{
 unsigned int dbyteA, dbyteB, highSurrogate, lowSurrogate;

 if(endianness != 2 && endianness != 1)
  return -4;

 if(p == NULL)
  return -1;

 if(result == NULL)
  return -1;



 if(endianness == 1)
 {
  dbyteA= *(p + 1);
  dbyteA <<= 8;
  dbyteA |= *(p + 0);


  dbyteB= *(p + 3);
  dbyteB <<= 8;
  dbyteB |= *(p + 2);
 }

 else
 {
  dbyteA= *(p + 0);
  dbyteA <<= 8;
  dbyteA |= *(p + 1);

  dbyteB= *(p + 2);
  dbyteB <<= 8;
  dbyteB |= *(p + 3);
 }

 if(dbyteA < 0xd800 || 0xdfff < dbyteA)
 {
  if(dbyteA > 0x10ffff)
   return -16;
  *result= dbyteA;


  return 2;
 }
# 392 "unicoder.c"
 if(0xd800 <= dbyteA && dbyteA <= 0xdbff)
 {
  if(0xdc00 <= dbyteB && dbyteB <= 0xdfff)
  {
   highSurrogate= dbyteA & 0x03ff;
   lowSurrogate= dbyteB & 0x03ff;

   *result= 0;
   *result |= highSurrogate;
   *result <<= 10;
   *result |= lowSurrogate;
   *result += 0x010000;


   return 4;
  }

  else
   return -8;
 }

 else
  return -8;

 return -1024;
}
