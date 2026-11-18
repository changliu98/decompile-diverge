int sum(int n)
{
  int sum = 0;
  int i;
  for (i = 1; i <= n; i++)
    sum += (2 * i - 1) * (2 * i - 1) * (2 * i - 1) * (2 * i - 1) * (2 * i - 1);
  return (sum);
}