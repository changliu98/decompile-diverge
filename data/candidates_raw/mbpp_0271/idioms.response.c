long sum(int n)
{
  long sum = 0;
  int i;
  for (i = 1; i <= n; i++)
    sum += i * 2 * i * 2 * i * 2 * i * 2 * i * 2;
  return (sum);
}