void test3(double *a, double *b, double *c, double *d) {
  int i = 0;
  for (i = 0; ; ++i) {
    if (i >= 11)
      break;
    c[i] = a[i] * b[i];
  }
  d[i] = a[i] * b[i];
}