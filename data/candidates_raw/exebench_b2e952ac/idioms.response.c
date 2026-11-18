void dsum(int n, double *y1, double *y2, double *y3, double *x1, double *x2, double *sum)
{
  double r00; double r01; double r10; double r11; double r20; double r21;
  double i00; double i01; double i10; double i11; double i20; double i21;
  int i; int j; int k;
  double y1j; double y2j; double y3j; double x1j; double x2j;
  r00 = r01 = r10 = r11 = r20 = r21 = 0.;
  i00 = i01 = i10 = i11 = i20 = i21 = 0.;
  for (i = j = k = 0; i < n; i++, j += 2, k += 2) {
    y1j = y1[j];
    y2j = y1[k];
    y3j = y2[j];
    x1j = x1[j];
    x2j = x1[k];
    r00 += y1j * x1j;
    i00 += y1j * x2j;
    r01 += y1j * x2j;
    i01 += y1j * x1j;
    r10 += y2j * x1j;
    i10 += y2j * x2j;
    r11 += y2j * x2j;
    i11 += y2j * x1j;
    r20 += y3j * x1j;
    i20 += y3j * x2j;
    r21 += y3j * x2j;
    i21 += y3j * x1j;
  }
  sum[0] = r00;
  sum[1] = i00;
  sum[2] = r01;
  sum[3] = i01;
  sum[4] = r10;
  sum[5] = i10;
  sum[6] = r11;
  sum[7] = i11;
  sum[8] = r20;
  sum[9] = i20;
  sum[10] = r21;
  sum[11] = i21;
}