size_t __cdecl utf8StrWidth(const char *s, size_t len)
{
  size_t skip; // [rsp+0h] [rbp-40h]
  uint32_t cp; // [rsp+Ch] [rbp-34h]
  size_t clen; // [rsp+10h] [rbp-30h] BYREF
  int after_zwj; // [rsp+1Ch] [rbp-24h]
  size_t i; // [rsp+20h] [rbp-20h]
  size_t width; // [rsp+28h] [rbp-18h]
  size_t lena; // [rsp+30h] [rbp-10h]
  const char *sa; // [rsp+38h] [rbp-8h]

  sa = s;
  lena = len;
  width = 0LL;
  i = 0LL;
  after_zwj = 0;
  while ( i < lena )
  {
    cp = utf8DecodeChar(&sa[i], &clen);
    if ( cp == 27 && (skip = ansiEscapeLen(&sa[i], lena - i)) != 0 )
    {
      i += skip;
    }
    else
    {
      if ( after_zwj )
        after_zwj = 0;
      else
        width += utf8CharWidth(cp);
      if ( isZWJ(cp) )
        after_zwj = 1;
      i += clen;
    }
  }
  return width;
}