int countPrime(int n)
{
  int count = 0;
  int i;
  for (i = 0; i < n; i++)
  {
    if (i > 1)
    {
      int isPrime = 1;
      int j;
      for (j = 2; j < i; j++)
      {
        if (i % j == 0)
        {
          isPrime = 0;
          break;
        }
      }
      if (isPrime)
      {
        count++;
      }
    }
  }
  return count;
}