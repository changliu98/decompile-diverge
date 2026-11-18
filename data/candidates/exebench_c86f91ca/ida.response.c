void __cdecl remove_dupc2(char *str)
{
  int v1; // ecx
  bool v2; // [rsp+1h] [rbp-11h]
  int j; // [rsp+2h] [rbp-10h]
  int ja; // [rsp+2h] [rbp-10h]
  int jb; // [rsp+2h] [rbp-10h]
  int i; // [rsp+6h] [rbp-Ch]
  int ia; // [rsp+6h] [rbp-Ch]

  for ( i = 0; str[i]; ++i )
  {
    if ( str[i] != -1 )
    {
      for ( j = i + 1; str[j]; ++j )
      {
        if ( str[i] == str[j] )
          str[j] = -1;
      }
    }
  }
  for ( ja = 0; ; ++ja )
  {
    v2 = 0;
    if ( str[ja] )
      v2 = str[ja] != -1;
    if ( !v2 )
      break;
  }
  if ( str[ja] )
    ia = ja;
  else
    ia = i - 1;
  for ( jb = ia + 1; str[jb]; ++jb )
  {
    if ( str[jb] != -1 )
    {
      v1 = ia++;
      str[v1] = str[jb];
    }
  }
  str[ia] = str[jb];
}