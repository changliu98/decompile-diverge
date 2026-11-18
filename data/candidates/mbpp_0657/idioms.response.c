int func0(int n)
{
  int i; int f = 1;
  for (i = 2; i <= n; i++)
    for (f *= i; f % 10 == 0; f /= 10);
  while (f >= 10)
    f /= 10;
  return (int)floor(f);
}