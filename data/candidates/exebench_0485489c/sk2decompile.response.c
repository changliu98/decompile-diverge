void crossp(double *a, double *b, double *c) {
  a[0] = b[1] * c[2] - b[2] * c[1];
  a[1] = b[2] * c[0] - b[0] * c[2];
  a[2] = b[0] * c[1] - b[1] * c[0];
}