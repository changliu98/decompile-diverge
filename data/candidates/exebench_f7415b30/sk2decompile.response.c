static int dummywc_mbtowc(wchar_t *pwc, const char *s, size_t n) {
  if (n < 1 || *s == '\0') return 0;
  *pwc = *s;
  return 1;
}