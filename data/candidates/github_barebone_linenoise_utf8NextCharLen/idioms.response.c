unsigned long utf8NextCharLen(char *text, unsigned long start, unsigned long len)
{
  if (start >= len)
    return 0;
  unsigned long total = 0;
  unsigned long curpos = start;
  unsigned int cp; unsigned int nextcp;
  unsigned long cplen; unsigned long nextlen;
  int isRI = 0;
  cp = UTF8_get_cp(&text[curpos], &cplen);
  total += cplen;
  curpos += cplen;
  isRI = UTF8_isRI(cp);
  while (curpos < len)
  {
    nextcp = UTF8_get_cp(&text[curpos], &nextlen);
    if (UTF8_isCR(nextcp) && (curpos + nextlen < len))
    {
      total += nextlen;
      curpos += nextlen;
      nextcp = UTF8_get_cp(&text[curpos], &nextlen);
      total += nextlen;
      curpos += nextlen;
    }
    else if (UTF8_isLF(nextcp))
    {
      total += nextlen;
      curpos += nextlen;
    }
    else
    {
      if (isRI && UTF8_isRI(nextcp))
      {
        total += nextlen;
        curpos += nextlen;
        isRI = 0;
      }
      else
        return total;
    }
  }
  return total;
}