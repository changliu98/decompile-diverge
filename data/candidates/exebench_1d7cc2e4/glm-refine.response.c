void __cdecl logFibonacci(int n, unsigned __int64 *fn1, unsigned __int64 *fn2)
{
  unsigned __int64 temp1;
  unsigned __int64 f1_sq;
  unsigned __int64 f2_sq;
  int m;

  if (n == 2)
  {
    *fn1 = 1LL;
    *fn2 = 1LL;
  }
  else if (n == 0)
  {
    *fn1 = 0LL;
    *fn2 = 0LL;
  }
  else
  {
    m = n / 2;
    if (m % 2) // Equivalent to (n / 2) % 2
    {
      logFibonacci(m - 1, fn1, fn2);
      
      // temp1 = F(m-1)^2 + 2 * F(m-1) * F(m-2)
      temp1 = *fn1 * *fn1 + 2 * *fn1 * *fn2;
      
      // *fn2 = F(m-1)^2 + F(m-2)^2 + temp1
      *fn2 = *fn1 * *fn1 + *fn2 * *fn2 + temp1;
      
      // *fn1 = temp1 + *fn2
      *fn1 = temp1 + *fn2;
    }
    else
    {
      logFibonacci(m, fn1, fn2);
      
      f1_sq = *fn1 * *fn1;
      f2_sq = *fn2 * *fn2;
      
      // *fn1 = F(m)^2 + 2 * F(m) * F(m-1)
      *fn1 = f1_sq + 2 * *fn1 * *fn2;
      
      // *fn2 = F(m)^2 + F(m-1)^2
      *fn2 = f1_sq + f2_sq;
    }
  }
}