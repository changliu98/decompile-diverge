int StrSafeCopy(char *dst, const char *src, int maxlen) {
  const char *s = src;
  int n = maxlen;
  if (n) {
    n--;
    if (n) {
      do {
        char c = *s++;
        *dst++ = c;
        if (!c) break;
      } while (--n);
    }
  }
  if (!n) {
    if (maxlen) *dst = '\0';
    while (*s++)
      ;
  }
  return s - src - 1;
}