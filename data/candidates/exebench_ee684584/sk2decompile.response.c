int clipmaxdouble(double *x, double max, long n) {
  long i;
  for (i = 0; i < n; i++) {
    if (x[i] > max) x[i] = max;
  }
  return 0;
}