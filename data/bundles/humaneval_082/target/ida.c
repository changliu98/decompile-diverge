bool __cdecl func0(const char *str)
{
  int i; // [rsp+8h] [rbp-18h]
  int l; // [rsp+Ch] [rbp-14h]

  l = strlen(str);
  if ( l < 2 )
    return 0;
  for ( i = 2; i * i <= l; ++i )
  {
    if ( !(l % i) )
      return 0;
  }
  return 1;
}