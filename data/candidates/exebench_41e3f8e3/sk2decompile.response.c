void table_norm(double *x, int n, double *y, int m, long *z, int k) {
  int i, j;
  for (j = 0; j < m; j++) {
    for (i = 0; i < n; i++) {
      if (x[i] > y[j]) {
        z[i]++;
      }
    }
  }
  for (j = 0; j < k; j++) {
    if (z[j] == 0) {
      z[j] = 1;
    }
  }
}