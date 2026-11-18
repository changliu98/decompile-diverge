void __cdecl Utf32toUtf8(unsigned int codepoint, char *utf8Buf)
{
  if ( codepoint >= 0x80 )
  {
    if ( codepoint >= 0x800 )
    {
      if ( codepoint >= 0x10000 )
      {
        if ( codepoint >= 0x200000 )
        {
          *utf8Buf = 63;
          utf8Buf[1] = 0;
        }
        else
        {
          *utf8Buf = (codepoint >> 18) | 0xF0;
          utf8Buf[1] = (codepoint >> 12) & 0x3F | 0x80;
          utf8Buf[2] = (codepoint >> 6) & 0x3F | 0x80;
          utf8Buf[3] = codepoint & 0x3F | 0x80;
          utf8Buf[4] = 0;
        }
      }
      else
      {
        *utf8Buf = (codepoint >> 12) | 0xE0;
        utf8Buf[1] = (codepoint >> 6) & 0x3F | 0x80;
        utf8Buf[2] = codepoint & 0x3F | 0x80;
        utf8Buf[3] = 0;
      }
    }
    else
    {
      *utf8Buf = (codepoint >> 6) | 0xC0;
      utf8Buf[1] = codepoint & 0x3F | 0x80;
      utf8Buf[2] = 0;
    }
  }
  else
  {
    *utf8Buf = codepoint;
    utf8Buf[1] = 0;
  }
}