char ***__cdecl func0(int m, int n, int o)
{
  char ***result = (char ***)malloc(8LL * o);
  
  for (int i = 0; i < o; ++i)
  {
    result[i] = (char **)malloc(8LL * n);
    
    for (int j = 0; j < n; ++j)
    {
      result[i][j] = (char *)malloc(m);
      
      for (int k = 0; k < m; ++k)
      {
        result[i][j][k] = '*'; // 42 is the ASCII code for '*'
      }
    }
  }
  
  return result;
}