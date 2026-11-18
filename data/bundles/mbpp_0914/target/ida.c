bool __cdecl func0(const char *s)
{
  int i; // [rsp+8h] [rbp-18h]
  int length; // [rsp+Ch] [rbp-14h]

  length = strlen(s);
  for ( i = 0; i < length - 2; ++i )
  {
    if ( s[i] != s[i + 2] )
      return 0;
  }
  return *s != s[1];
}