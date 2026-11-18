void cmul(double *a, double *b) {
  double t;
  t = a[0] * b[1] + a[1] * b[0];
  a[0] = a[0] * b[0] - a[1] * b[1];
  a[1] = t;
}