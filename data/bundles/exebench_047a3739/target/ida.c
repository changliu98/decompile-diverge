void __cdecl squeeze(char *s1, const char *s2)
{
  unsigned int v2; // ecx
  bool v3; // [rsp+1h] [rbp-1Dh]
  unsigned int k; // [rsp+2h] [rbp-1Ch]
  unsigned int j; // [rsp+6h] [rbp-18h]
  unsigned int i; // [rsp+Ah] [rbp-14h]

  j = 0;
  i = 0;
  while ( s1[j] )
  {
    for ( k = 0; ; ++k )
    {
      v3 = 0;
      if ( s2[k] )
        v3 = s1[j] != s2[k];
      if ( !v3 )
        break;
    }
    if ( !s2[k] )
    {
      v2 = i++;
      s1[v2] = s1[j];
    }
    ++j;
  }
  s1[i] = 0;
}