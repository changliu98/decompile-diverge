static void calc_speed(double *x0, double *x1, double *x2, double dt)
{
  int i, j, k;
  double a, b;
  for (j = 0; j <= 18; j += 6) {
    for (i = 0; i < 3; i++) {
      k = j + i;
      b = (x2[k] - x0[k]) / 2;
      a = (x2[k] + x0[k]) / 2 - x1[k];
      x1[k+3] = (2 * a + b) / dt;
    }
  }
}