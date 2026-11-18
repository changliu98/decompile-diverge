unsigned long utf8StrWidth(char *s, unsigned long len)
{
  char *sp = s;
  unsigned long sl = len;
  unsigned long width = 0;
  unsigned long i = 0;
  int after_zwj = 0;
  while (i < sl) {
    unsigned int c = wstrchar(&sp[i], &len);
    if (c == 0x1b && (len = wstrskip(&sp[i], sl - i)) > 0) {
      i += len;
    } else {
      if (after_zwj)
        after_zwj = 0;
      else
        width += wstrwidth1(c);
      if (wstriszwj(c))
        after_zwj = 1;
      i += len;
    }
  }
  return width;
}