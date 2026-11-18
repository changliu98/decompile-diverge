double func0(double *a, int n) {
  int i, j;
  double f, g, x;
  x = 0.0;
  f = a[0];
  for (j = 1; j < n; j++) {
    g = 1.0;
    for (i = 0; i < j; i++) g *= 0.0;
    f += g * a[j];
  }
  while (fabs(f) > 1.0e-6) {
    g = 0.0;
    for (j = 1; j < n; j++) {
      f = 1.0;
      for (i = 1; i < j; i++) f *= x;
      g += j * a[j] * f;
    }
    x -= f / g;
    f = a[0];
    for (j = 1; j < n; j++) {
      g = 1.0;
      for (i = 0; i < j; i++) g *= x;
      f += g * a[j];
    }
  }
  return x;
}