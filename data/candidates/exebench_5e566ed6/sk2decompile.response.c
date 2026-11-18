int fit_line(double *x, double *y, int n, double *m, double *b) {
  int i;
  double sx, sxy, sy, sxx, denom;
  sx = 0.0;
  sxy = 0.0;
  sy = 0.0;
  sxx = 0.0;
  for (i = 0; i < n; i++) {
    sxx += x[i];
    sx += x[i] * x[i];
    sy += y[i];
    sxy += x[i] * y[i];
  }
  denom = (double)n * sx - sxx * sxx;
  if (denom == 0.0) return -1;
  *m = (sy * sx - sxx * sxy) / denom;
  *b = (n * sxy - sxx * sy) / denom;
  return 0;
}