void rifft2pt(float *x, float scale) {
  float a, b, c, d;
  a = x[0] + x[1];
  b = x[0] - x[1];
  c = 2.0 * x[2];
  d = 2.0 * x[3];
  x[0] = scale * (a + c);
  x[1] = scale * (b - d);
  x[2] = scale * (a - c);
  x[3] = scale * (b + d);
}