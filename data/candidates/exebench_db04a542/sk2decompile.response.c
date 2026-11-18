char *checkpath(char *dst, const char *src) {
  char *d = dst;
  const char *s = src;
  if (dst && src) {
    while (*s) {
      if (*s == '\\') {
        *d++ = '/';
        s++;
      } else {
        *d++ = *s++;
      }
    }
    *d = *s;
  }
  return dst;
}