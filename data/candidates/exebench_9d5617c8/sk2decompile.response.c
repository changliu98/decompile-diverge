void ifft2pt(float *x, float scale) {
  float a, b, c, d;
  a = x[0];
  b = x[1];
  c = x[2];
  d = x[3];
  x[0] = scale * (a + c);
  x[1] = scale * (b + d);
  x[2] = scale * (a - c);
  x[3] = scale * (b - d);
}