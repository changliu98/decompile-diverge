int gcdEx(int a, int b, int *x, int *y)
{
  if (b == 0)
  {
    *x = 1;
    *y = 0;
    return a;
  }
  int t = *x;
  int d = gcdEx(b, a % b, y, x);
  t = *x;
  *x = *y;
  *y = t - a / b * *y;
  return d;
}