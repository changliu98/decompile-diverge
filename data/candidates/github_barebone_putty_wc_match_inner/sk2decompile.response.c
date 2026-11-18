int wc_match_inner(const char *pattern, const char *string,
                   unsigned int string_len) {
  const char *p = pattern;
  const char *s = string;
  const char *end = string + string_len;
  int r;
  if (*p != '*') {
    r = wc_match_fragment(&p, &s, end);
    if (r <= 0) return r;
  }
  while (*p) {
    do {
      if (!(*p == '*'))
        _fail("*p == '*'", "func.c", 228,
              "int wc_match_inner(const char *, const char *, unsigned int)");
    } while (0);
    while (*p == '*') p++;
    if (!*p) return 1;
    r = 0;
    while (*s) {
      const char *p_save = p;
      const char *s_save = s;
      r = wc_match_fragment(&p, &s, end);
      if (r < 0) return r;
      if (r > 0 && !*p && s != end) {
        s = s_save + (end - s);
        p = p_save;
        return wc_match_fragment(&p, &s, end);
      }
      if (r > 0) break;
      s++;
    }
    if (r <= 0) return 0;
  }
  return s == end;
}