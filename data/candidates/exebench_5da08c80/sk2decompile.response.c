int mmeq(float *a, float *b, int m, int n) {
  int i;
  for (i = 0; i < m * n; i++) {
    if (a[i] != b[i]) {
      return 0;
    }
  }
  return 1;
}