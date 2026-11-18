bool __cdecl func0(const char *brackets)
{
  int i; // [rsp+8h] [rbp-18h]
  int level; // [rsp+Ch] [rbp-14h]

  level = 0;
  for ( i = 0; i < strlen(brackets); ++i )
  {
    if ( brackets[i] == 40 )
      ++level;
    if ( brackets[i] == 41 )
      --level;
    if ( level < 0 )
      return 0;
  }
  return level == 0;
}