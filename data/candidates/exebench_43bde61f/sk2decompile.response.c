void mlPointAddTo(float *a, float *b, float *c) {
  unsigned int i;
  for (i = 0; i < 3; i++) {
    c[i] = a[i] + b[i];
  }
}