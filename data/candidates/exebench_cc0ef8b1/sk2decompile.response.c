float xCorrCoef(float *x, float *y, int n) {
  int i;
  float sum_xy = 0.0;
  float sum_y = 0.0;
  for (i = 0; i < n; i++) {
    sum_xy += x[i] * y[i];
    sum_y += y[i] * y[i];
  }
  if (sum_xy > 0)
    return sum_xy * sum_xy / sum_y;
  else
    return 0.0;
}