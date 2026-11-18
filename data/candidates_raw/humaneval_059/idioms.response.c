int prime(int n)
{
  int i = 2;
  for (i = 2; i * i <= n; i++)
  {
    while (n % i == 0)
    {
      if (n / i > i)
        n /= i;
      else
        break;
    }
  }
  return n;
}