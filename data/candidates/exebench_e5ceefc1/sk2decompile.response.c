int set1d(double *a, double val) {
  int i;
  for (i = 0; i < 40; i++) {
    a[i] = val;
  }
  return 0;
}