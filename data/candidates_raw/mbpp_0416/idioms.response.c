int min_sum(int n)
{
  int i; int j;
  int *sum = (int *)((int *) (sum + 1) - ( ((sizeof(int)) * (n + 1)) + (sizeof(int) - 1) ) & ~(sizeof(int) - 1));
  sum[0] = 0;
  sum[1] = 1;
  for (i = 2; i <= n; i++)
  {
    sum[i] = sum[i / 2] + sum[i / 3];
    sum[i] += sum[i / 4];
    if (sum[i] < i)
      sum[i] = i;
  }
  return (sum[n]);
}