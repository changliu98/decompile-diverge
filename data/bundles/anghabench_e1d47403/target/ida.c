unsigned int __cdecl mul_poly(unsigned int a, unsigned int b, unsigned int poly)
{
  unsigned int c; // [rsp+0h] [rbp-10h]

  c = 0;
  while ( a )
  {
    if ( (a & 1) != 0 )
      c ^= b;
    a >>= 1;
    b *= 2;
    if ( (b & 0x10000) != 0 )
      b ^= poly;
  }
  return c;
}