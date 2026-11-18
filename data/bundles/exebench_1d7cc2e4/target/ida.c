void __cdecl logFibonacci(int n, unsigned __int64 *fn1, unsigned __int64 *fn2)
{
  unsigned __int64 v3; // rax
  unsigned __int64 v4; // rcx
  unsigned __int64 temp1_0; // [rsp+8h] [rbp-38h]
  int m; // [rsp+24h] [rbp-1Ch]

  if ( n == 2 )
  {
    *fn2 = 1LL;
    *fn1 = 1LL;
  }
  else if ( n )
  {
    m = n / 2;
    if ( n / 2 % 2 )
    {
      logFibonacci(m - 1, fn1, fn2);
      temp1_0 = *fn1 * *fn1 + *fn1 * 2 * *fn2;
      *fn2 = *fn1 * *fn1 + *fn2 * *fn2 + temp1_0;
      *fn1 = temp1_0 + *fn2;
    }
    else
    {
      logFibonacci(m, fn1, fn2);
      v3 = *fn2 * *fn2;
      v4 = *fn1 * *fn1;
      *fn1 = v4 + *fn1 * 2 * *fn2;
      *fn2 = v4 + v3;
    }
  }
  else
  {
    *fn2 = 0LL;
    *fn1 = 0LL;
  }
}