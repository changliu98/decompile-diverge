void sum_xy(int n, double *y0, double *y1, double *x0, double *x1, double *x2, double *sums)
{
  double r00 = 0.; double i00 = 0.; double r01 = 0.; double i01 = 0.; double r02 = 0.; double i02 = 0.;
  double r10 = 0.; double i10 = 0.; double r11 = 0.; double i11 = 0.; double r12 = 0.; double i12 = 0.;
  int i = 0; int j = 1; int k = 0;
  for (k = 0; k < n; i += 2, j += 2, k++)
  {
    double y0i = y0[i]; double y0j = y0[j];
    double y1i = y1[i]; double y1j = y1[j];
    double x0i = x0[i]; double x0j = x0[j];
    double x1i = x1[i]; double x1j = x1[j];
    double x2i = x2[i]; double x2j = x2[j];
    r00 += (y0i * x0i);
    i00 += (y0i * x0j);
    r01 += (y0i * x1i);
    i01 += (y0i * x1j);
    r02 += (y0i * x2i);
    i02 += (y0i * x2j);
    r10 += (y1i * x0i);
    i10 += (y1i * x0j);
    r11 += (y1i * x1i);
    i11 += (y1i * x1j);
    r12 += (y1i * x2i);
    i12 += (y1i * x2j);
  }
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r02;
  sums[5] = i02;
  sums[6] = r10;
  sums[7] = i10;
  sums[8] = r11;
  sums[9] = i11;
  sums[10] = r12;
  sums[11] = i12;
}