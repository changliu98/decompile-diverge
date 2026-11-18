void logFibonacci(int n, long *fn1, long *fn2)
{
  if (n == 2)
  {
    *fn2 = 1;
    *fn1 = 1;
  }
  else if (n == 0)
  {
    *fn2 = 0;
    *fn1 = 0;
  }
  else
  {
    int m = n / 2;
    if (m % 2 == 0)
    {
      logFibonacci(m, fn1, fn2);
      long temp = *fn1 * *fn1;
      temp += *fn1 * *fn2 * 2;
      *fn1 += *fn1 * *fn2 * 2;
      *fn2 += temp;
    }
    else
    {
      logFibonacci(m - 1, fn1, fn2);
      long temp = *fn1 * *fn1 * 2;
      temp += *fn1 * *fn2 * 2;
      *fn2 += *fn1 * *fn1 * 2;
      *fn2 += *fn1 * *fn1;
      *fn1 += *fn2;
      *fn1 += temp;
    }
  }
}