void splini(double *x, double *y, double *dy, int n, double xx, double *yy) {
  int i, j;
  double h, a, b, a2, b2, xi, yi, yyi;
  yyi = 0.0;
  j = 0;
  for (i = 1; xx > x[j] && i < n; i++) {
    xi = xx;
    if (i < n - 1) {
      if (xi > x[i]) xi = x[i];
    }
    h = x[i] - x[j];
    a = (x[i] - xi) / h;
    b = (xi - x[j]) / h;
    a2 = a * a;
    b2 = b * b;
    yi = a * (1.0 - a2) / 2.0 + b2 * y[i] / 2.0 +
         h * h *
             ((-(a2 * (1.0 + a2) / 4.0) + a2 / 2.0) * dy[j] +
              (b2 * (1.0 - b2) / 4.0 - b2 / 2.0) * dy[i]) /
             6.0;
    yyi += h * yi;
    j++;
  }
  *yy = yyi;
}