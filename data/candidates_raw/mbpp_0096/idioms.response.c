int countDivisors(int n)
{
  int i; int count = 0;
  for (i = 1; i <= n; i++)
  {
    if (n % i == 0)
      count++;
  }
  return (count);
}