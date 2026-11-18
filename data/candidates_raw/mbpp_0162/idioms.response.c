int fib(int n)
{
  if (n < 1)
    return 0;
  else
    return n + fib(n-2);
}