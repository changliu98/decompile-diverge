char *vips_utf8_strcasestr(const char *haystack, const char *needle,
                           int maxlen) {
  const char *p;
  const char *q;
  int nlen;
  int mlen;
  int len;
  nlen = g_utf8_strlen(needle, -1);
  mlen = strlen(needle);
  p = haystack;
  while (p - haystack <= maxlen - mlen) {
    const char *s1 = p;
    const char *s2 = needle;
    int i;
    for (i = 0; i < nlen; i++) {
      gunichar c1 = g_utf8_get_char_validated(s1, haystack + maxlen - p);
      gunichar c2 = g_utf8_get_char_validated(s2, -1);
      if (c1 == (unsigned int)-1 || c1 == (unsigned int)-2 ||
          c2 == (unsigned int)-1 || c2 == (unsigned int)-2)
        return NULL;
      if (c1 == 0) return NULL;
      if (g_unichar_tolower(c1) != g_unichar_tolower(c2)) break;
      s1 = g_utf8_find_next_char(s1, haystack + maxlen);
      s2 = g_utf8_find_next_char(s2, NULL);
    }
    if (i == nlen) return (char *)p;
    p = g_utf8_find_next_char(p, NULL);
  }
  return NULL;
}