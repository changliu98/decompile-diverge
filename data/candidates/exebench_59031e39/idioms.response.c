double my_modf(double x, double *iptr)
{
  double x0 = x;
  double *ip = iptr;
  double x1 = x;
  double f = 1.0;
  int i;
  for (i = 0; i < 100; i++) {
    long l = (long) x1;
    if (l + 1 < (long) x1 || l > (long) x1 - 1) {
      x1 = x1 * 0.1;
      f = f * 10.0;
    }
    else
      break;
  }
  if (i == 100) {
    *ip = 0.0;
    return 0.0;
  }
  else if (i == 0) {
    *ip = (long) x1;
    return x - *ip;
  }
  else {
    double ipart;
    return my_modf(x0 - f * (long) x1, &ipart) + f * (long) x1 + ipart;
  }
}