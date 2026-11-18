int is_empty(float *a, int n) {
  int i;
  for (i = 0; i <= n; i++) {
    if (a[i] > 1.175494351e-38) {
      return 0;
    }
  }
  return 1;
}