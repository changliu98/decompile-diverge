int extEuclid(int a, int b, int *x, int *y)
{
  int t;
  if (b == 0) {
    *x = 1;
    *y = 0;
    return a;
  }
  t = *x;
  *x = *y;
  *y = t - *x * (a / b);
  return gcdEx(b, a % b, x, y);
}