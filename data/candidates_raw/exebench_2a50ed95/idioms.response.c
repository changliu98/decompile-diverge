void csum(int n, double *y0, double *y1, double *x0, double *sums)
{
  double r00 = 0.0;
  double i00 = 0.0;
  double r10 = 0.0;
  double i10 = 0.0;
  int i = 0;
  int r = 0;
  int i1 = 1;
  for (int j = 0; j < n; j++) {
    double yr0 = y0[r];
    double yi0 = y0[i1];
    double yr1 = y1[r];
    double yi1 = y1[i1];
    double xr0 = x0[r];
    double xi0 = x0[i1];
    r00 += (yr0 * xr0) + (yi0 * xi0);
    i00 += (yr0 * xi0) - (yi0 * xr0);
    r10 += (yr1 * xr0) + (yi1 * xi0);
    i10 += (yr1 * xi0) - (yi1 * xr0);
    i++;
    r = r + 2;
    i1 = i1 + 2;
  }
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r10;
  sums[3] = i10;
}