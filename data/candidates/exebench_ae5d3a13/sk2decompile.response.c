void sum(double *x, int n, double *s) {
  int i;
  double sum = 0.0;
  for (i = 0; i < n; i++) {
    sum += x[i];
  }
  *s = sum;
}