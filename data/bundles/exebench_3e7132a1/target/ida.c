int __cdecl chartorune(unsigned __int16 *rune, const char *str)
{
  __int16 c2; // [rsp+Ch] [rbp-24h]
  unsigned __int16 c1; // [rsp+10h] [rbp-20h]
  unsigned __int16 c; // [rsp+14h] [rbp-1Ch]

  c = *(unsigned __int8 *)str;
  if ( *(unsigned __int8 *)str >= 0x80u )
  {
    c1 = *((unsigned __int8 *)str + 1) ^ 0x80;
    if ( (c1 & 0xC0) == 0 )
    {
      if ( *(unsigned __int8 *)str >= 0xE0u )
      {
        c2 = *((unsigned __int8 *)str + 2) ^ 0x80;
        if ( (c2 & 0xC0) == 0
          && *(unsigned __int8 *)str < 0xF0u
          && (unsigned __int16)(c2 | ((c1 | (unsigned __int16)(c << 6)) << 6)) > 0x7FFuLL )
        {
          *rune = c2 | ((c1 | (unsigned __int16)(c << 6)) << 6);
          return 3;
        }
      }
      else if ( *(unsigned __int8 *)str >= 0xC0u && ((c1 | (unsigned __int16)(c << 6)) & 0x7FFu) > 0x7FuLL )
      {
        *rune = (c1 | (c << 6)) & 0x7FF;
        return 2;
      }
    }
    *rune = 128;
    return 1;
  }
  *rune = c;
  return 1;
}