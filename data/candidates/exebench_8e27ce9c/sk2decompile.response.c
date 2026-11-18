void DFT2(float *x, float *w) {
  float t;
  t = x[0] + x[1];
  x[1] = x[0] - x[1];
  x[0] = t;
}