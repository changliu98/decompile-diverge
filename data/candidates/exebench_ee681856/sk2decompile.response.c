void c_saxpy(int n, double a, double *x, double *y) {
  int i, m;
  if (n <= 0) return;
  if (a == 0.0) return;
  m = n % 4;
  if (m != 0) {
    for (i = 1; i <= m; i++) {
      y[i - 1] += a * x[i - 1];
    }
  }
  for (i = m + 1; i <= n; i += 4) {
    y[i - 1] += a * x[i - 1];
    y[i] += a * x[i];
    y[i + 1] += a * x[i + 1];
    y[i + 2] += a * x[i + 2];
  }
}