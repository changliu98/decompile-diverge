bool __cdecl func0(const char *s)
{
  int i; // [rsp+Ch] [rbp-14h]

  if ( strlen(s) < 3 )
    return 0;
  for ( i = 2; i < strlen(s); ++i )
  {
    if ( s[i] == s[i - 1] || s[i] == s[i - 2] )
      return 0;
  }
  return 1;
}