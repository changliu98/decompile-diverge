float modf(int a, int c, int m, float *x)
{
  *x = (*x * a + c - m * (int)(*x * a + c) / m) / m;
  return *x;
}