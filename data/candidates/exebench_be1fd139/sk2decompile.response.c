void r3sums(double *a, double s, double *b, double t) {
  a[0] = s * b[0] + t * b[1];
  a[1] = s * b[1] + t * b[2];
  a[2] = s * b[2] + t * b[0];
}