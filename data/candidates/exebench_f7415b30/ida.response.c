int __cdecl dummywc_mbtowc(int *pwc, const char *s, size_t n)
{
  if ( !n || !*s )
    return 0;
  *pwc = *s;
  return 1;
}