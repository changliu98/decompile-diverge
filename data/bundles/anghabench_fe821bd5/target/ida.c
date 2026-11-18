int __cdecl ok_cp1251(char *s, int n)
{
  int i; // [rsp+0h] [rbp-18h]

  for ( i = 1; i < n; ++i )
  {
    if ( s[i] == -104 )
      return 0;
  }
  return 1;
}