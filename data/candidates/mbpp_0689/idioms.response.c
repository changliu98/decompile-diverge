int func0(int *array, int n)
{
  int *end = array + n;
  int *sum = (int *) ( ( ( (char *) end ) + ( ( sizeof(int) * ( n ) ) + ( sizeof(char) * ( -1 ) ) ) & ( ( -1 ) & ~ ( sizeof(char) * ( -1 ) ) ) ) );
  int i; int j;
  int max; int max_end;
  if ( n == 0 || array[0] == 0 )
  {
    max = 0x7fffffff;
    max_end = 1;
  }
  else
  {
    sum[0] = 0;
    for ( i = 1; i < n; i++ )
    {
      sum[i] = 0x7fffffff;
      for ( j = 0; j < i; j++ )
      {
        if ( i > j + array[j] )
          continue;
        if ( sum[j] == 0x7fffffff )
          continue;
        int new_sum = (sum[i] < sum[j] + 1 ? sum[i] : sum[j] + 1);
        sum[i] = new_sum;
        break;
      }
    }
    max = sum[n - 1];
    max_end = 1;
  }
  return max;
}