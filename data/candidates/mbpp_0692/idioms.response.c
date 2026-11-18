int func0(int n)
{
  int i; int fac;
  if (n > 9)
    return 0;
  fac = 1;
  for (i = 1; i <= n; i++)
    fac = (fac * i) % 100;
  return fac;
}