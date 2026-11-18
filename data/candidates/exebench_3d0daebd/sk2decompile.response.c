void swt_max(double *x, int n, double *max) {
  int i;
  *max = x[0];
  for (i = 1; i < n; i++) {
    if (x[i] > *max) {
      *max = x[i];
    }
  }
}