int __cdecl runetochar(char *s, int c)
{
  int ca; // [rsp+0h] [rbp-14h]

  ca = c;
  if ( c >= 128 )
  {
    if ( c >= 2048 )
    {
      if ( c > 1114111 )
        ca = 65533;
      if ( ca >= 4096 )
      {
        *s = (ca >> 18) | 0xF0;
        s[1] = (ca >> 12) & 0x3F | 0x80;
        s[2] = (ca >> 6) & 0x3F | 0x80;
        s[3] = ca & 0x3F | 0x80;
        return 4;
      }
      else
      {
        *s = (ca >> 12) | 0xE0;
        s[1] = (ca >> 6) & 0x3F | 0x80;
        s[2] = ca & 0x3F | 0x80;
        return 3;
      }
    }
    else
    {
      *s = (c >> 6) | 0xC0;
      s[1] = c & 0x3F | 0x80;
      return 2;
    }
  }
  else
  {
    *s = c;
    return 1;
  }
}