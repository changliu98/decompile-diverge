float max(float *x, int n) {
  int i;
  float max = -10000;
  for (i = 0; i < n; i++) {
    if (x[i] > max) max = x[i];
  }
  return max;
}