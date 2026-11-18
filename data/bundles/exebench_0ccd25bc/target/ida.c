int __cdecl unicoder_utf32_decode(unsigned int *result, unsigned __int8 *p, unsigned int endianness)
{
  unsigned int decoded; // [rsp+0h] [rbp-24h]
  int i; // [rsp+4h] [rbp-20h]

  if ( endianness != 2 && endianness != 1 )
    return -4;
  if ( !p )
    return -1;
  if ( !result )
    return -1;
  decoded = 0;
  for ( i = 0; i < 4; ++i )
  {
    if ( endianness == 2 )
    {
      if ( i > 0 )
        decoded <<= 8;
      decoded |= p[i];
    }
    else
    {
      if ( i > 0 )
        decoded >>= 8;
      decoded |= p[i] << 24;
    }
  }
  if ( decoded > 0x10FFFF )
    return -16;
  if ( decoded >= 0xD800 && decoded <= 0xDFFF )
    return -16;
  *result = decoded;
  return 4;
}