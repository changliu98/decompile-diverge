void maxind(double *x, int n, double *max, double *ind) {
  int i;
  *max = x[0];
  *ind = 0.0;
  for (i = 1; i < n; i++) {
    if (x[i] > *max) {
      *max = x[i];
      *ind = (double)i;
    }
  }
}