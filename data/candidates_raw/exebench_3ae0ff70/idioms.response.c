void mul16(unsigned int a, unsigned int b, unsigned int *hi, unsigned int *lo)
{
  unsigned int ahi = a>>16;
  unsigned int alo = a&0xFFFF;
  unsigned int bhi = b>>16;
  unsigned int blo = b&0xFFFF;
  unsigned int a1 = alo * blo;
  unsigned int a2 = alo * bhi;
  unsigned int a3 = bhi * blo;
  unsigned int a4 = a1>>16;
  unsigned int a5 = a2>>16;
  unsigned int a6 = a3>>16;
  unsigned int a7 = a1 & 0xFFFF;
  unsigned int a8 = a2 & 0xFFFF;
  unsigned int a9 = a3 & 0xFFFF;
  *hi = a4 + a5 + a6 + (a7 + a8 + a9>>16)>>16;
  *lo = a7 + a8 + a9 & 0xFFFF0000UL;
}