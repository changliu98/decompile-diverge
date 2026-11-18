void dot(float *a, float *b, float *c) {
  int i;
  *c = 0.0;
  for (i = 0; i < 4; i++) {
    *c += a[i] * b[i];
  }
}