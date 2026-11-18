void func0(float *x, int n, float *y) {
  int i;
  for (i = 1; i < n; i++) {
    y[i - 1] = i * x[i];
  }
}