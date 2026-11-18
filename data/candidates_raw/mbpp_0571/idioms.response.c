int maxsum(int *array, int n, int k)
{
  int *sum;
  int i; int max;
  qsort(array, n, sizeof(int), cmpfunc);
  sum = (int *)malloc(n * sizeof(int));
  sum[0] = 0;
  for (i = 1; i < n; i++)
  {
    sum[i] = sum[i - 1];
    if (array[i] - array[i - 1] < k)
    {
      if (i < 2)
      {
        if (sum[i] > array[i - 1] + array[i])
          sum[i] = sum[i];
        else
          sum[i] = array[i - 1] + array[i];
      }
      else
      {
        if (sum[i] > array[i - 1] + array[i] + sum[i - 2])
          sum[i] = sum[i];
        else
          sum[i] = array[i - 1] + array[i] + sum[i - 2];
      }
    }
  }
  max = sum[n - 1];
  free(sum);
  return (max);
}