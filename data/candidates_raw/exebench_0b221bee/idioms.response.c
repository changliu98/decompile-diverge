static double d_log2(double x, int *exp)
{
  double y = x;
  int e = 0;
  double s = 1.;
  if (y < 0)
  {
    y = -y;
    s = -1.;
  }
  if (y != 0.)
  {
    while (y >= 1.)
    {
      y = y * 0.5;
      e++;
    }
    while (y < 0.5)
    {
      y = y * 2.;
      e--;
    }
  }
  *exp = e;
  return s * y;
}