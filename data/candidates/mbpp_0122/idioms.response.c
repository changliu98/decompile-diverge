int func0(int n)
{
  int i;
  int j;
  int k;
  int temp;
  int na = n;
  int primes[-1];
  int result[-1];
  memset(primes, 0, sizeof(primes));
  result[0] = 0;
  for (i = 2; i < 3000; i++)
  {
    if (primes[i] == 0)
    {
      primes[i] = 1;
      for (j = i * 2; j < 3000; j += i)
      {
        if (primes[j]-- == -3)
        {
          result[result[0]++] = j;
        }
      }
    }
  }
  for (i = 0; i < result[0] - 1; i++)
  {
    for (j = 0; j < result[0] - i - 1; j++)
    {
      if (result[j] > result[j + 1])
      {
        temp = result[j];
        result[j] = result[j + 1];
        result[j + 1] = temp;
      }
    }
  }
  return result[na - 1];
}