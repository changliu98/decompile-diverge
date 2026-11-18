void ZVdotU21(int n, double *x, double *y, double *z, double *v) {
  int i, j, k;
  double xr, xi, yr, yi, xr1, xi1, yr1, yi1;
  xr = xi = yr = yi = 0.0;
  i = 0;
  j = 0;
  k = 1;
  for (; j < n; j++, i += 2, k += 2) {
    xr1 = x[i];
    xi1 = x[k];
    yr1 = y[i];
    yi1 = y[k];
    yr = z[i];
    yi = z[k];
    xr += xr1 * yr - xi1 * yi;
    xi += xr1 * yi + xi1 * yr;
    yr = yr1 * yr - yi1 * yi;
    yi = yr1 * yi + yi1 * yr;
    xr += yr;
    xi += yi;
  }
  v[0] = xr;
  v[1] = xi;
  v[2] = yr;
  v[3] = yi;
}