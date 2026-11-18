void project(int n, double *x, int *mask) {
  int i;
  for (i = 0; i < n; i++) {
    if (mask[i]) {
      x[i] = 0.0;
    }
  }
}