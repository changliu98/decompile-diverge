int fib(int n)
{
  if ( n < 3 )
    return n;
  int a = 1;
  int b = 2;
  int c = a + b * 2;
  for (int i = 3; i <= n; i++)
  {
    a = b;
    b = c;
    c = a + b * 2;
  }
  return b;
}