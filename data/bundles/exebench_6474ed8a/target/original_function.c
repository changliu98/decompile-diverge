static int gen256(unsigned char dst[256], unsigned int prim_poly)
{
 unsigned int identity;
 int i;
 unsigned int v;




 if ((prim_poly & 0x100) == 0)
  return -1;
# 91 "fec.c"
 identity = prim_poly & 0xff;





 dst[0] = 0;
 dst[1] = 1;
# 113 "fec.c"
 v = 1;
 for (i = 2; i < 256; i++) {
  v <<= 1;
  if (v & 0x100) {
   v &= 0xff;
   v ^= identity;
  }
  dst[i] = v;
 }

 return 0;
}