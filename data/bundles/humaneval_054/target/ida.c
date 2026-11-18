bool __cdecl func0(const char *s0, const char *s1)
{
  int j_0; // [rsp+8h] [rbp-38h]
  bool found_0; // [rsp+Fh] [rbp-31h]
  int i_0; // [rsp+10h] [rbp-30h]
  int j; // [rsp+14h] [rbp-2Ch]
  bool found; // [rsp+1Bh] [rbp-25h]
  int i; // [rsp+1Ch] [rbp-24h]
  int len1; // [rsp+20h] [rbp-20h]
  int len0; // [rsp+24h] [rbp-1Ch]

  len0 = strlen(s0);
  len1 = strlen(s1);
  for ( i = 0; i < len0; ++i )
  {
    found = 0;
    for ( j = 0; j < len1; ++j )
    {
      if ( s0[i] == s1[j] )
      {
        found = 1;
        break;
      }
    }
    if ( !found )
      return 0;
  }
  for ( i_0 = 0; i_0 < len1; ++i_0 )
  {
    found_0 = 0;
    for ( j_0 = 0; j_0 < len0; ++j_0 )
    {
      if ( s1[i_0] == s0[j_0] )
      {
        found_0 = 1;
        break;
      }
    }
    if ( !found_0 )
      return 0;
  }
  return 1;
}