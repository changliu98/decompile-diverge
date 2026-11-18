double d2t(double d, double a)
{
  if (a > 360.0)
    return -1.0;
  return d * (a / 360.0) * (1.0 / (22.0 / 7.0));
}