float spline_cubic_val(int n, float *x, float xval, float *y, float *m) {
  int i, k;
  float dx, h, dm, dmh, a, b;
  k = n - 2;
  for (i = 0; i < n - 1; i++) {
    if (xval < x[i + 1]) {
      k = i;
      break;
    }
  }
  dx = xval - x[k];
  h = x[k + 1] - x[k];
  dm = y[k + 1] - y[k];
  dmh = m[k + 1] - m[k];
  a = dmh / (6.0 * h);
  b = dm / h;
  return y[k] + dx * (m[k] / 3.0 + dx * (a + dx / 2.0) - b * h);
}