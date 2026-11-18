void heaviside(double *x, double *y, double *z) {
  int i;
  int n = y - x + 1;
  *z = 1.0;
  for (i = 0; i < n; i++) {
    *z = (*z == 1.0 && x[i] >= 0.0) ? 1.0 : 0.0;
  }
}