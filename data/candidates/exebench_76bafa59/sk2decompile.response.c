void rifft1pt(float *x, float scale) {
  float x0, x1;
  x0 = x[0];
  x1 = x[1];
  x[0] = scale * (x0 + x1);
  x[1] = scale * (x0 - x1);
}