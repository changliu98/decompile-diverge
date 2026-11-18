int func0(int n)
{
  int i;
  int sum = 0;

  for (i = 1; i <= n; i++)
    {
      int tmp = 2 * i - 1;
      sum += tmp * tmp * tmp * tmp;
    }

  return sum;
}