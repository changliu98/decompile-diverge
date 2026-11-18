void innerdct(double *x, double *y, double *c) {
  double a0, a1, a2, a3, a4, a5, a6, a7;
  a0 = x[0] + x[7];
  a1 = x[1] + x[6];
  a2 = x[2] + x[5];
  a3 = x[3] + x[4];
  a4 = a0 + a3;
  a5 = a1 + a2;
  a6 = a0 - a3;
  a7 = a1 - a2;
  y[0] = a4 * c[4] + a5 * c[4];
  y[32] = a4 * c[4] - a5 * c[4];
  y[16] = a6 * c[2] + a7 * c[6];
  y[48] = a6 * c[6] + a7 * c[2];
  a0 = x[0] - x[7];
  a1 = x[1] - x[6];
  a2 = x[2] - x[5];
  a3 = x[3] - x[4];
  a4 = a0 + a3;
  a5 = a1 + a2;
  a6 = a0 - a3;
  a7 = a1 - a2;
  y[8] = a4 * c[1] + a5 * c[3] + a6 * c[7] + a7 * c[5];
  y[24] = -a4 * c[3] + a5 * c[1] - a6 * c[5] + a7 * c[7];
  y[40] = a4 * c[5] + a5 * c[7] + a6 * c[3] - a7 * c[1];
  y[56] = -a4 * c[7] + a5 * c[5] - a6 * c[1] + a7 * c[3];
}