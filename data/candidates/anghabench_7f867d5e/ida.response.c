uint8_t __cdecl gfmul(uint8_t a, uint8_t b)
{
  char v2; // cl
  uint8_t v; // [rsp+1h] [rbp-3h]

  v = 0;
  while ( b )
  {
    if ( (b & 1) != 0 )
      v ^= a;
    v2 = 0;
    if ( (a & 0x80) != 0 )
      v2 = 29;
    a = v2 ^ (2 * a);
    b = (int)b >> 1;
  }
  return v;
}