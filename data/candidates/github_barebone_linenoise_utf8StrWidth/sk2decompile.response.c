unsigned long utf8StrWidth(const char *str, unsigned long len) {
  const char *s = str;
  unsigned long l = len;
  unsigned long width = 0;
  unsigned long i = 0;
  int skip = 0;
  while (i < l) {
    unsigned int c;
    unsigned int clen;
    c = utf8DecodeChar(s + i, &clen);
    if (c == 27) {
      unsigned int len2 = ansiEscapeLen(s + i, l - i);
      if (len2) {
        i += len2;
        continue;
      }
    }
    if (skip)
      skip = 0;
    else
      width += utf8CharWidth(c);
    if (isZWJ(c)) skip = 1;
    i += clen;
  }
  return width;
}