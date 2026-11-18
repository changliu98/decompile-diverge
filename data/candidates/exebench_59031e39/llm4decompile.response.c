double my_modf(double x, double *iptr)
{
  double i, f;
  double factor = 1.0;
  int i_int;
  int n;

  for (n = 0; n < 100; n++) {
    i = (double) (int) (x + 0.5);
    f = x - i;
    if (f >= 0.0 && f <= 0.5)
      break;
    x *= 10.0;
    factor *= 10.0;
  }

  if (n == 100) {
    *iptr = 0.0;
    return 0.0;
  }

  if (n == 0) {
    *iptr = x;
    return x - *iptr;
  }

  i_int = (int) (x / factor);
  f = my_modf(x - i_int * factor, iptr);
  *iptr += i_int * factor;
  return f;
}