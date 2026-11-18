static long utf8len(char *s)
{
  char *p = s;
  long len;
  while (*p) {
    len = utf8charlen(*p);
    if (len == -1)
      return -1;
    ++p;
    for (len -= 1; len > 0; --len) {
      if ((*p & 0xc0) != 0x80)
        return -1;
      ++p;
    }
  }
  return p - s;
}