void __cdecl squeeze_alt(char *str1, char *str2)
{
  int v2; // ecx
  bool v3; // [rsp+1h] [rbp-21h]
  int found; // [rsp+2h] [rbp-20h]
  int k; // [rsp+6h] [rbp-1Ch]
  int j; // [rsp+Ah] [rbp-18h]
  int i; // [rsp+Eh] [rbp-14h]

  j = 0;
  for ( i = 0; str1[i]; ++i )
  {
    found = 0;
    for ( k = 0; ; ++k )
    {
      v3 = 0;
      if ( str2[k] )
        v3 = found != 1;
      if ( !v3 )
        break;
      if ( str1[i] == str2[k] )
        found = 1;
    }
    if ( !found )
    {
      v2 = j++;
      str1[v2] = str1[i];
    }
  }
  str1[j] = 0;
}