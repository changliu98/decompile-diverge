static double double_log2(double x, int *exp)
{
  double y = x;
  int e = 0;
  double s = 1.0;
  if (y < 0.0)
  {
    y = -y;
    s = -1.0;
  }
  if (y != 0.0)
  {
    while (y >= 1.0)
    {
      y = y * 0.5;
      e++;
    }
    while (y < 0.5)
    {
      y = y * 2.0;
      e--;
    }
  }
  *exp = e;
  return y * s;
}