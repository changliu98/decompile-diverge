void sum_product(int n, double *y0, double *y1, double *y2, double *x0, double *x1, double *sums)
{
  double r00 = 0.0; double r01 = 0.0; double r10 = 0.0; double r11 = 0.0; double r20 = 0.0; double r21 = 0.0;
  double i00 = 0.0; double i01 = 0.0; double i10 = 0.0; double i11 = 0.0; double i20 = 0.0; double i21 = 0.0;
  int i = 0; int j = 0; int k = 1;
  for (i = 0; i < n; i++, j += 2, k += 2)
  {
    double y0i = y0[j];
    double y1i = y1[j];
    double y2i = y2[j];
    double x0i = x0[j];
    double x1i = x1[j];
    double y0k = y0[k];
    double y1k = y1[k];
    double y2k = y2[k];
    double x0k = x0[k];
    double x1k = x1[k];
    r00 += y0i * x0i;
    i00 += y0i * x0k - y0k * x0i;
    r01 += y0i * x1i;
    i01 += y0i * x1k - y0k * x1i;
    r10 += y1i * x0i;
    i10 += y1i * x0k - y1k * x0i;
    r11 += y1i * x1i;
    i11 += y1i * x1k - y1k * x1i;
    r20 += y2i * x0i;
    i20 += y2i * x0k - y2k * x0i;
    r21 += y2i * x1i;
    i21 += y2i * x1k - y2k * x1i;
  }
  sums[0] = r00;
  sums[1] = i00;
  sums[2] = r01;
  sums[3] = i01;
  sums[4] = r10;
  sums[5] = i10;
  sums[6] = r11;
  sums[7] = i11;
  sums[8] = r20;
  sums[9] = i20;
  sums[10] = r21;
  sums[11] = i21;
}