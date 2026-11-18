void prod_vet(float *a, float *b, float *c) {
  a[2] = -b[1] * c[0] + b[0] * c[1];
  b[2] = -c[1] * a[0] + c[0] * a[1];
  c[2] = -a[1] * b[0] + a[0] * b[1];
}