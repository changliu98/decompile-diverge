void __cdecl utf8_encode(int val, char *utf8_str)
{
  int len; // [rsp+0h] [rbp-14h]

  len = 0;
  if ( (unsigned int)val > 0x7F )
  {
    if ( val < 128 || val > 2047 )
    {
      if ( val < 2048 || val > 0xFFFF )
      {
        if ( val >= 0x10000 && val <= 1114111 )
        {
          utf8_str[3] = val & 0x3F | 0x80;
          utf8_str[2] = (val >> 6) & 0x3F | 0x80;
          utf8_str[1] = (val >> 12) & 0x3F | 0x80;
          *utf8_str = (val >> 18) & 7 | 0xF0;
          len = 4;
        }
      }
      else
      {
        utf8_str[2] = val & 0x3F | 0x80;
        utf8_str[1] = (val >> 6) & 0x3F | 0x80;
        *utf8_str = (val >> 12) & 0xF | 0xE0;
        len = 3;
      }
    }
    else
    {
      utf8_str[1] = val & 0x3F | 0x80;
      *utf8_str = (val >> 6) & 0x1F | 0xC0;
      len = 2;
    }
  }
  else
  {
    *utf8_str = val & 0x7F;
    len = 1;
  }
  utf8_str[len] = 0;
}