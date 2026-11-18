void __cdecl yxyDES2_Int2Bits(unsigned int _src, char *dstBits)
{
  unsigned int i;

  for ( i = 0; i < 4; ++i )
    dstBits[i] = (_src >> (3 - i)) & 1;
}