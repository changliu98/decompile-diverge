char *__cdecl fix(char *d, char *s)
{
  int v2; // ecx
  int di_0; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]

  i = 0;
  di_0 = 0;
  while ( s[i] )
  {
    if ( s[i] == 8 )
    {
      if ( --di_0 < 0 )
        di_0 = 0;
    }
    else
    {
      v2 = di_0++;
      d[v2] = s[i];
    }
    ++i;
  }
  d[di_0] = 0;
  return d;
}