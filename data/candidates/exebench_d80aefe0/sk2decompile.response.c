float vdot(float *a, float *b) {
  float c;
  c = a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
  return c;
}