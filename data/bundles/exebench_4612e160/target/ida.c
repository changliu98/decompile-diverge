unsigned int __cdecl utf8_decode_v2(const char *utf8char, size_t size, size_t *charlen)
{
  if ( size && *utf8char )
  {
    if ( (*utf8char & 0x80) != 0 )
    {
      if ( (*utf8char & 0xE0) == 192 )
      {
        if ( charlen )
          *charlen = 2LL;
        if ( size >= 2 && utf8char[1] )
          return utf8char[1] & 0x3F | ((*utf8char & 0x1F) << 6);
        else
          return -1;
      }
      else if ( (*utf8char & 0xF0) == 224 )
      {
        if ( charlen )
          *charlen = 3LL;
        if ( size >= 3 && utf8char[1] && utf8char[2] )
          return utf8char[2] & 0x3F | ((utf8char[1] & 0x3F) << 6) | ((*utf8char & 0xF) << 12);
        else
          return -1;
      }
      else if ( (*utf8char & 0xF8) == 240 )
      {
        if ( charlen )
          *charlen = 4LL;
        if ( size >= 4 && utf8char[1] && utf8char[2] && utf8char[3] )
          return utf8char[3] & 0x3F | ((utf8char[2] & 0x3F) << 6) | ((utf8char[1] & 0x3F) << 12) | ((*utf8char & 7) << 15);
        else
          return -1;
      }
      else
      {
        if ( charlen )
          *charlen = 0LL;
        return -1;
      }
    }
    else
    {
      if ( charlen )
        *charlen = 1LL;
      return *utf8char & 0x7F;
    }
  }
  else
  {
    if ( charlen )
      *charlen = 0LL;
    return -1;
  }
}