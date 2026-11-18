void __cdecl yxyDES2_Int2Bits(unsigned int _src, char *dstBits)
{
  unsigned int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 4; ++i )
    dstBits[i] = ((_src << i) & 8) >> 3;
}