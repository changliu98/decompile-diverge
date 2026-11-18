void get_sum(int n, double *y0, double *x0, double *x1, double *x2, double *sums)
{
  double r00 = 0.; double r01 = 0.; double r02 = 0.;
  double i00 = 0.; double i01 = 0.; double i02 = 0.;
  int i = 0; int r = 0; int i1 = 1;
  for (i = 0; i < n; i++, r += 2, i1 += 2) {
    double yr0 = y0[r]; double yr1 = y0[i1];
    double xr0 = x0[r]; double xr1 = x1[r]; double xr2 = x2[r];
    double xi0 = x0[i1]; double xi1 = x1[i1]; double xi2 = x2[i1];
    r00 += yr0 * xr0 + yr1 * xi0;
    i00 += yr0 * xi0 - yr1 * xr0;
    r01 += yr0 * xr1 + yr1 * xi1;
    i01 += yr0 * xi1 - yr1 * xr1;
    r02 += yr0 * xr2 + yr1 * xi2;
    i02 += yr0 * xi2 - yr1 * xr2;
  }
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r02;
  sums[5] = i02;
}