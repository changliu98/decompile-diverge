void convolve_4(double *out, const double *a, const double *b) {
  double a0 = a[0];
  double b0 = b[0];
  double a1 = a[1];
  double b1 = b[1];
  out[0] = a0 * b0;
  double a2 = a[2];
  double b2 = b[2];
  out[1] = a0 * b1 + a1 * b0;
  double a3 = a[3];
  double b3 = b[3];
  out[2] = a0 * b2 + a1 * b1 + a2 * b0;
  out[3] = a0 * b3 + a1 * b2 + a2 * b1 + a3 * b0;
  out[4] = a1 * b3 + a2 * b2 + a3 * b1;
  out[5] = a2 * b3 + a3 * b2;
  out[6] = a3 * b3;
}