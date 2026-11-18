static double frexp(double d, int *exp)
{
  double f = d;
  int sign = 1;
  if (f < 0) {
    sign = -1;
    f = -f;
  }
  else if (f == 0.0) {
    *exp = 0;
    return 0.0;
  }
  *exp = 0;
  int e = 1;
  for (f = d; ; f /= e) {
    int i = f >= 0.5;
    if (i)
      i = f >= 1.0;
    if (!i)
      break;
    e *= 2;
    (*exp)++;
  }
  return f * sign;
}