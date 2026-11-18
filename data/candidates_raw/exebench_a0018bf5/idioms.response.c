void quat_mul(double *a, double *b, double *c)
{
  double a11 = a[0] + a[7];
  double a12 = a[1] + a[6];
  double a13 = a[2] + a[5];
  double a14 = a[3] + a[4];
  double b1 = a11 + a14 * c[4];
  double b2 = a12 + a13 * c[4];
  b[0] = b1;
  b[32] = b1 - b2;
  b[16] = (a11 - a14) * c[2] + (a12 - a13) * c[6];
  b[48] = (a11 - a14) * c[6] + (a13 - a12) * c[2];
  a11 = a[0] - a[7];
  a12 = a[1] - a[6];
  a13 = a[2] - a[5];
  a14 = a[3] - a[4];
  b[8] = a11 * c[1] + a12 * c[3] + a13 * c[5] + a14 * c[7];
  b[24] = a11 * c[3] - a12 * c[1] + a13 * c[7] - a14 * c[5];
  b[40] = a11 * c[5] - a12 * c[7] + a13 * c[1] - a14 * c[3];
  b[56] = a11 * c[7] - a12 * c[5] + a13 * c[3] - a14 * c[1];
}