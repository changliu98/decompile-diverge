int func0(int n, int a, int b)
{
  int isp = n >= 2;
  int i = 2;
  for (i = 2; i * i <= n; i++)
    if (n % i == 0)
      isp = 0;
  if (isp)
    return a;
  return b;
}