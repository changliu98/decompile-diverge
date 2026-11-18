size_t __cdecl utf8NextCharLen(const char *buf, size_t pos, size_t len)
{
  uint32_t nextcp; // [rsp+4h] [rbp-4Ch]
  size_t nextlen; // [rsp+8h] [rbp-48h] BYREF
  int isRI; // [rsp+10h] [rbp-40h]
  uint32_t cp; // [rsp+14h] [rbp-3Ch]
  size_t cplen; // [rsp+18h] [rbp-38h] BYREF
  size_t curpos; // [rsp+20h] [rbp-30h]
  size_t total; // [rsp+28h] [rbp-28h]
  size_t lena; // [rsp+30h] [rbp-20h]
  size_t posa; // [rsp+38h] [rbp-18h]
  const char *bufa; // [rsp+40h] [rbp-10h]

  bufa = buf;
  posa = pos;
  lena = len;
  if ( pos >= len )
    return 0LL;
  total = 0LL;
  curpos = posa;
  cp = utf8DecodeChar(&bufa[posa], &cplen);
  total += cplen;
  curpos += cplen;
  isRI = isRegionalIndicator(cp);
  while ( curpos < lena )
  {
    nextcp = utf8DecodeChar(&bufa[curpos], &nextlen);
    if ( isZWJ(nextcp) && nextlen + curpos < lena )
    {
      total += nextlen;
      curpos += nextlen;
      utf8DecodeChar(&bufa[curpos], &nextlen);
      total += nextlen;
      curpos += nextlen;
    }
    else if ( isGraphemeExtend(nextcp) )
    {
      total += nextlen;
      curpos += nextlen;
    }
    else
    {
      if ( !isRI || !isRegionalIndicator(nextcp) )
        return total;
      total += nextlen;
      curpos += nextlen;
      isRI = 0;
    }
  }
  return total;
}