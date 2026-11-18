void ZVdotC31(int n, double *y0, double *y1, double *y2, double *x0, double *sums)
{
  double r00 = 0.; double r10 = 0.; double r20 = 0.;
  double i00 = 0.; double i10 = 0.; double i20 = 0.;
  int i = 0; int j = 0; int k = 1;
  for (i = 0; i < n; i++, j += 2, k += 2) {
    double yr0 = y0[j]; double yr1 = y1[j]; double yr2 = y2[j];
    double yrk = y0[k]; double yrk1 = y1[k]; double yrk2 = y2[k];
    double xr0 = x0[j]; double xr1 = x0[k];
    double xrk = x0[k];
    r00 += yr0 * xr0 + yrk * xrk;
    i00 += yr0 * xrk - yrk * xr0;
    r10 += yr1 * xr0 + yrk1 * xrk;
    i10 += yr1 * xrk - yrk1 * xr0;
    r20 += yr2 * xr0 + yrk2 * xrk;
    i20 += yr2 * xrk - yrk2 * xr0;
  }
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r10;
  sums[3] = i10;
  sums[4] = r20;
  sums[5] = i20;
  return;
}