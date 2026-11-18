int bell(int n)
{
  int i; int j;
  unsigned long long **array;
  array = (unsigned long long **)malloc((n+1)*sizeof(unsigned long long *));
  for(i = 0; i <= n; i++)
  {
    array[i] = (unsigned long long *)malloc((n+1)*sizeof(unsigned long long));
    for(j = 0; j <= n; j++)
    {
      array[i][j] = 0;
    }
  }
  array[0][0] = 1;
  for(i = 1; i <= n; i++)
  {
    array[i][0] = array[i-1][i-1];
    for(j = 1; j <= i; j++)
    {
      array[i][j] = array[i][j-1] + array[i-1][j-1];
    }
  }
  int result = (int)array[0][0];
  for(i = 0; i <= n; i++)
  {
    free(array[i]);
  }
  free(array);
  return result;
}