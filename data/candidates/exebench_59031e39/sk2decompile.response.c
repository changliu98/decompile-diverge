double my_modf(double x, double *iptr) {
  double x_orig = x;
  double scale = 1.0;
  double x_scale;
  long x_long;
  int i;
  x_scale = x_orig;
  scale = 1.0;
  for (i = 0; i < 100; i++) {
    x_long = (long)x_scale;
    if (x_scale + 1.0 >= (double)x_long && x_scale - 1.0 <= (double)x_long)
      break;
    x_scale *= 0.1;
    scale *= 10.0;
  }
  if (i == 100) {
    *iptr = 0.0;
    return 0.0;
  }
  if (i == 0) {
    *iptr = (double)x_long;
    return x_scale - *iptr;
  }
  double iptr_scale;
  double ret = my_modf(x - (double)x_long * scale, &iptr_scale);
  *iptr = iptr_scale + (double)x_long * scale;
  return ret;
}