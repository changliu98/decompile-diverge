void ZVdotC21(int n, double *x, double *y, double *z, double *v) {
  int i, j, k;
  double sr, si, tr, ti, xr, xi, yr, yi;
  sr = si = tr = ti = 0.0;
  i = 0;
  j = 0;
  k = 1;
  for (; j < n; j++, i += 2, k += 2) {
    xr = x[i];
    xi = x[k];
    yr = y[i];
    yi = y[k];
    tr = z[i];
    ti = z[k];
    sr += xr * tr + xi * ti;
    si += xr * ti - xi * tr;
    tr = yr * tr + yi * ti;
    ti = yr * ti - yi * tr;
    sr += tr;
    si += ti;
  }
  v[0] = sr;
  v[1] = si;
  v[2] = tr;
  v[3] = ti;
}