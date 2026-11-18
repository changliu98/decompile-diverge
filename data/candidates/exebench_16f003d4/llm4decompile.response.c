void calc_speed(double *x0, double *x1, double *x2, double dt)
{
  int i, j;
  double a, b;

  for (j = 0; j < 19; j += 6) {
    for (i = 0; i < 3; i++) {
      a = (x2[i+j] - x0[i+j]) / 2.0;
      b = (x2[i+j] + x0[i+j]) / 2.0 - x1[i+j];
      x1[i+j+3] = (2.0*b + a) / dt;
    }
  }

  return;
}