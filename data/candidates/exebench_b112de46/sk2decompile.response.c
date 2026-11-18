void af_filter_bilinear(float *b, float *a, float x, float *y, float *d) {
  float b0, a0;
  b0 = b[0] + 2 * b[1] * x + 4 * b[2] * x * x;
  a0 = a[0] + 2 * a[1] * x + 4 * a[2] * x * x;
  *y *= b0 / a0;
  d[0] = (2 * a[0] - 8 * a[2] * x * x) / a0;
  d[1] = (4 * a[2] * x * x - 2 * a[1] + a[0]) / a0;
  d[2] = (2 * b[0] - 8 * b[2] * x * x) / b0;
  d[3] = (4 * b[2] * x * x - 2 * b[1] + b[0]) / b0;
}