void mult(double *a, double *b, double *c) {
  int i, j;
  for (i = 0, j = 0; i < 4; i++) {
    c[i] = a[j] * b[0];
    c[i] += a[j + 1] * b[1];
    c[i] += a[j + 2] * b[2];
    c[i] += a[j + 3] * b[3];
    j += 4;
  }
}