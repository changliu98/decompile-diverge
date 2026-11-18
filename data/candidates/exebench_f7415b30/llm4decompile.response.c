int
dummywc_mbtowc (ucs4_t *pwc, const unsigned char *s, size_t n)
{
  if (n > 0 && *s != '\0') {
    *pwc = *s;
    return 1;
  } else
    return 0;
}