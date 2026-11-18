void ZVdotC13(int n, double *x, double *y, double *z, double *w, double *v) {
  int i, j, k;
  double v0, v1, v2, v3, v4, v5, x0, x1, y0, y1, z0, z1;
  v0 = v1 = v2 = v3 = v4 = v5 = 0.0;
  i = 0;
  j = 0;
  k = 1;
  for (; j < n; j++, i += 2, k += 2) {
    x0 = x[i];
    x1 = x[k];
    y0 = y[i];
    y1 = y[k];
    z0 = z[i];
    z1 = z[k];
    v2 = x0 * y0 + x1 * y1 + v2;
    v3 = x0 * y1 - x1 * y0 + v3;
    v0 = x0 * z0 + x1 * z1 + v0;
    v1 = x0 * z1 - x1 * z0 + v1;
    v4 = x0 * y0 + x1 * y1 + v4;
    v5 = x0 * y1 - x1 * y0 + v5;
  }
  v[0] = v2;
  v[1] = v3;
  v[2] = v0;
  v[3] = v1;
  v[4] = v4;
  v[5] = v5;
}