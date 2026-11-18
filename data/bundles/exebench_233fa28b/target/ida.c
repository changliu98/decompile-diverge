size_t __cdecl utf8BytesToCodePoint(const char *buf, size_t len, int *cp)
{
  unsigned __int8 byte; // [rsp+1h] [rbp-21h]

  if ( !len )
    return 0LL;
  byte = *buf;
  if ( (*buf & 0x80) != 0 )
  {
    if ( (byte & 0xE0) == 192 )
    {
      if ( len >= 2 )
      {
        *cp = buf[1] & 0x3F | ((*buf & 0x1F) << 6);
        return 2LL;
      }
    }
    else if ( (byte & 0xF0) == 224 )
    {
      if ( len >= 3 )
      {
        *cp = buf[2] & 0x3F | ((buf[1] & 0x3F) << 6) | ((*buf & 0xF) << 12);
        return 3LL;
      }
    }
    else if ( (byte & 0xF8) == 240 && len >= 4 )
    {
      *cp = buf[3] & 0x3F | ((buf[2] & 0x3F) << 6) | ((buf[1] & 0x3F) << 12) | ((*buf & 7) << 18);
      return 4LL;
    }
    return 0LL;
  }
  *cp = byte;
  return 1LL;
}