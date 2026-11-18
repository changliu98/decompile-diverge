void max1D_double(double *x, int n, double *max) {
  int i;
  max[0] = -1;
  max[1] = -DBL_MAX;
  for (i = 0; i < n; i++) {
    if (x[i] > max[1]) {
      max[1] = x[i];
      max[0] = i;
    }
  }
}