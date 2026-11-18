void cftx020(double *a) {
  double a0p2, a1p3;
  a0p2 = a[0] - a[2];
  a1p3 = a[1] - a[3];
  a[0] += a[2];
  a[1] += a[3];
  a[2] = a0p2;
  a[3] = a1p3;
}