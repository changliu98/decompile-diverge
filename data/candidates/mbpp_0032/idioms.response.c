int func0(int n)
{
  int maxPrime = -1;
  int i;
  for (i = 2; i < n; i++)
  {
    if (n % i == 0)
    {
      maxPrime = i;
      n /= i;
    }
  }
  return maxPrime;
}