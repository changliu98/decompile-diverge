int __cdecl func0(char *s)
{
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int n; // [rsp+10h] [rbp-10h]
  int result; // [rsp+14h] [rbp-Ch]

  result = 0;
  n = strlen(s);
  for ( i = 0; i < n; ++i )
  {
    for ( j = 1; j <= n - i; ++j )
    {
      if ( check_Equality(s, i, j + i - 1) )
        ++result;
    }
  }
  return result;
}