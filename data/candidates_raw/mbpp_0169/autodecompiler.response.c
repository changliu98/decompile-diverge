int fib(int n)
{
  int f[31];
  int i;
  if(n <= 2)
    return f[n] = n;
  else
  {
    f[1] = 1;
    f[2] = 2;
    for(i = 3; i <= n; i++)
      f[i] = f[i-1] + f[i-2];
    return f[i-1];
  }
}