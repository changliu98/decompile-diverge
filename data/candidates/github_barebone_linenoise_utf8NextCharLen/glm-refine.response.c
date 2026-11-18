size_t __cdecl utf8NextCharLen(const char *buf, size_t pos, size_t len)
{
  size_t nextlen;
  int isRI;
  char32_t cp;
  char32_t nextcp;
  size_t cplen;
  size_t curpos;
  size_t total;

  if (pos >= len)
    return 0;

  total = 0;
  curpos = pos;

  cp = utf8DecodeChar(&buf[pos], &cplen);
  total += cplen;
  curpos += cplen;

  isRI = isRegionalIndicator(cp);

  while (curpos < len)
  {
    nextcp = utf8DecodeChar(&buf[curpos], &nextlen);

    if (isZWJ(nextcp) && nextlen + curpos < len)
    {
      total += nextlen;
      curpos += nextlen;
      utf8DecodeChar(&buf[curpos], &nextlen);
      total += nextlen;
      curpos += nextlen;
    }
    else if (isGraphemeExtend(nextcp))
    {
      total += nextlen;
      curpos += nextlen;
    }
    else
    {
      if (!isRI || !isRegionalIndicator(nextcp))
        return total;

      total += nextlen;
      curpos += nextlen;
      isRI = 0;
    }
  }

  return total;
}