int __cdecl UnicodeToUtf8(unsigned int src, char *dest)
{
  int len; // [rsp+0h] [rbp-14h]
  char *desta; // [rsp+4h] [rbp-10h]

  desta = dest;
  len = 0;
  if ( src > 0x7F )
  {
    if ( src > 0x7FF )
    {
      if ( src != 65279 && (src < 0xD800 || src > 0xDFFF) && src <= 0xFFFF )
      {
        *dest = (src >> 12) | 0xE0;
        dest[1] = (src >> 6) & 0x3F | 0x80;
        desta = dest + 3;
        dest[2] = src & 0x3F | 0x80;
        len = 3;
      }
    }
    else
    {
      *dest = (src >> 6) | 0xC0;
      desta = dest + 2;
      dest[1] = src & 0x3F | 0x80;
      len = 2;
    }
  }
  else
  {
    desta = dest + 1;
    *dest = src;
    len = 1;
  }
  *desta = 0;
  return len;
}