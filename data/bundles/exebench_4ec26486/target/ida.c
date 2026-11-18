void __cdecl squeeze_all(char *s, char *b)
{
  int v2; // ecx
  int badchar; // [rsp+0h] [rbp-20h]
  int k; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]

  k = 0;
  for ( i = 0; s[i]; ++i )
  {
    badchar = 0;
    for ( j = 0; b[j]; ++j )
    {
      if ( s[i] == b[j] )
        badchar = 1;
    }
    if ( !badchar )
    {
      v2 = k++;
      s[v2] = s[i];
    }
  }
  s[k] = 0;
}