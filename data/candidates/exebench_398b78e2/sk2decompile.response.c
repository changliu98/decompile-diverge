float reson(float x, float *coef) {
  float y;
  y = x * coef[0] + coef[1] * coef[3] - coef[2] * coef[4];
  coef[4] = coef[3];
  coef[3] = y;
  return y;
}