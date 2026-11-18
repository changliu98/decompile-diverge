void unscale(double *x, unsigned int n) {
  unsigned int i;
  double scale = 8.636168555094445e-78;
  for (i = 0; i < n; i++) {
    *x *= scale;
  }
}