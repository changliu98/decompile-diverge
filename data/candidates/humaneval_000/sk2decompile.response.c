int _is_duplicated(float *x, int n, float eps) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = i + 1; j < n; j++) {
      if (fabs(x[i] - x[j]) < eps) {
        return 1;
      }
    }
  }
  return 0;
}