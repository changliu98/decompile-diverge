int func0(int n)
{
  int sum = 0;
  int i = 2;
  for (i = 2; i * i <= n; i++)
  {
    while (n % i == 0)
    {
      sum += i;
      n /= i;
    }
  }
  return sum + n;
}