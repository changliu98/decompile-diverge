bool __cdecl func0(const char *brackets)
{
  int i; // [rsp+0h] [rbp-18h]
  int level; // [rsp+4h] [rbp-14h]

  level = 0;
  for ( i = 0; brackets[i]; ++i )
  {
    if ( brackets[i] == 60 )
      ++level;
    if ( brackets[i] == 62 )
      --level;
    if ( level < 0 )
      return 0;
  }
  return level == 0;
}