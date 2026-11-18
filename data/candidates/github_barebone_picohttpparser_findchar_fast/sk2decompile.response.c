static const char *findchar_fast(const char *start, const char *end,
                                 const char *chars, unsigned int nchars,
                                 int *found) {
  const char *p;
  *found = 0;
  for (p = start; p < end; p++) {
    unsigned int i;
    for (i = 0; i < nchars; i++) {
      if (*p == chars[i]) {
        *found = 1;
        return p;
      }
    }
  }
  return p;
}