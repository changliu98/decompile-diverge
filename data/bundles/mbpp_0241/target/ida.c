char ***__cdecl func0(int m, int n, int o)
{
  int k; // [rsp+Ch] [rbp-24h]
  int j; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]
  char ***result; // [rsp+18h] [rbp-18h]

  result = (char ***)malloc(8LL * o);
  for ( i = 0; i < o; ++i )
  {
    result[i] = (char **)malloc(8LL * n);
    for ( j = 0; j < n; ++j )
    {
      result[i][j] = (char *)malloc(m);
      for ( k = 0; k < m; ++k )
        result[i][j][k] = 42;
    }
  }
  return result;
}