void daxpy(int n, double a, double *x, double *y) {
  if (a == 0.0) return;
  if (a == 1.0) {
    do {
      y[--n] += x[n];
    } while (n);
  } else {
    do {
      y[--n] += a * x[n];
    } while (n);
  }
}