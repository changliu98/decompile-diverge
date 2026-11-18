int __cdecl denormal_addf1(unsigned int ix, unsigned int iy)
{
  int exp; // [rsp+0h] [rbp-14h]
  int frac; // [rsp+4h] [rbp-10h]
  unsigned int iya; // [rsp+8h] [rbp-Ch]

  if ( ix < 0x800000 )
    return iy + ix;
  exp = (ix & 0x7F800000) >> 23;
  if ( exp - 1 > 31 )
    return ix;
  iya = iy >> (exp - 1);
  if ( !iya )
    return ix;
  frac = (ix & 0x7FFFFF | 0x800000) + iya;
  if ( frac >= 0x1000000 )
  {
    frac >>= 1;
    ++exp;
  }
  return frac & 0x7FFFFF | (exp << 23);
}