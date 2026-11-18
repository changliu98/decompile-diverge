int __cdecl tt_unesc(char *s, char esc)
{
  int n; // [rsp+0h] [rbp-2Ch]
  char *dst; // [rsp+4h] [rbp-28h]

  n = 0;
  while ( *s != esc )
  {
    if ( !*s )
      return 0;
    ++s;
  }
  dst = s;
  while ( *s )
  {
    if ( *s == esc )
    {
      ++s;
      ++n;
    }
    *dst++ = *s++;
  }
  return n;
}