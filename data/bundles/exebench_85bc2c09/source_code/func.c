#include <memory.h>

void yxyDES2_Int2Bits(unsigned int _src, char* dstBits)
{
 unsigned int i=0;
 for(i=0; i < 4; i++)
  dstBits[i] = ((_src<<i) & 8)>>3;
}
