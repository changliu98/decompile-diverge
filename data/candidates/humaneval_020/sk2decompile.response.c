void __minmax(float *x, int n, float *y) {
  int i, j;
  float min = 3.402823466e+38F;
  float diff;
  int tmp;
  y[0] = x[0];
  y[1] = x[1];
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      diff = fabs(x[i] - x[j]);
      if (diff < min) {
        min = diff;
        y[0] = x[i];
        y[1] = x[j];
      }
    }
  }
  if (y[0] > y[1]) {
    tmp = y[0];
    y[0] = y[1];
    y[1] = tmp;
  }
}