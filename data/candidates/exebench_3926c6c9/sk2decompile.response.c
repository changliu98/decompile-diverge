void ne_pre_filter8_double(double *out, double *in, int *coeffs) {
  double a0 = in[0] - in[7];
  double a1 = in[1] - in[6];
  double a2 = in[2] - in[5];
  double a3 = in[3] - in[4];
  double a4 = in[3] - a3 / 2.0;
  double a5 = in[2] - a2 / 2.0;
  double a6 = in[1] - a1 / 2.0;
  double a7 = in[0] - a0 / 2.0;
  double b0 = a3 * coeffs[0] / 16.0;
  double b1 = a2 * coeffs[1] / 16.0;
  double b2 = a1 * coeffs[2] / 16.0;
  double b3 = a0 * coeffs[3] / 16.0 + b2 * coeffs[6] / 16.0;
  double b4 = b2 + b3 * coeffs[9] / 16.0 + b1 * coeffs[5] / 16.0;
  double b5 = b1 + b4 * coeffs[8] / 16.0 + b0 * coeffs[4] / 16.0;
  double b6 = b0 + b5 * coeffs[7] / 16.0;
  out[0] = a7 + b3 / 2.0;
  out[1] = a6 + b4 / 2.0;
  out[2] = a5 + b5 / 2.0;
  out[3] = a4 + b6 / 2.0;
  out[4] = a4 - b6;
  out[5] = a5 - b5;
  out[6] = a6 - b4;
  out[7] = a7 - b3;
}