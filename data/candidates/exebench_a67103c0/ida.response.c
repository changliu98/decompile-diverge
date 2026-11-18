int __cdecl unicoder_utf16_decode(unsigned int *result, unsigned __int8 *p, unsigned int endianness)
{
  unsigned int dbyteB; // [rsp+8h] [rbp-24h]
  unsigned int dbyteA; // [rsp+Ch] [rbp-20h]

  if ( endianness != 2 && endianness != 1 )
    return -4;
  if ( !p )
    return -1;
  if ( !result )
    return -1;
  if ( endianness == 1 )
  {
    dbyteA = *(unsigned __int16 *)p;
    dbyteB = *((unsigned __int16 *)p + 1);
  }
  else
  {
    dbyteA = (*p << 8) | p[1];
    dbyteB = (p[2] << 8) | p[3];
  }
  if ( dbyteA >= 0xD800 && dbyteA <= 0xDFFF )
  {
    if ( dbyteA > 0xDBFF )
    {
      return -8;
    }
    else if ( dbyteB < 0xDC00 || dbyteB > 0xDFFF )
    {
      return -8;
    }
    else
    {
      *result = 0;
      *result |= dbyteA & 0x3FF;
      *result <<= 10;
      *result |= dbyteB & 0x3FF;
      *result += 0x10000;
      return 4;
    }
  }
  else if ( dbyteA <= 0x10FFFF )
  {
    *result = dbyteA;
    return 2;
  }
  else
  {
    return -16;
  }
}