void crossproduct(float *c, float *a, float *b) {
  c[0] = b[1] * a[2] - b[2] * a[1];
  c[1] = b[2] * a[0] - b[0] * a[2];
  c[2] = b[0] * a[1] - b[1] * a[0];
}