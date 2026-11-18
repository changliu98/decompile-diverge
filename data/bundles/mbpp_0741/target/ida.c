bool __cdecl func0(const char *s)
{
  int i; // [rsp+8h] [rbp-18h]
  int n; // [rsp+Ch] [rbp-14h]

  n = strlen(s);
  for ( i = 1; i < n; ++i )
  {
    if ( s[i] != *s )
      return 0;
  }
  return 1;
}