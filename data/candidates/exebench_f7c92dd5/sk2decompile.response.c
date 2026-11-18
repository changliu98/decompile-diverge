void dot4(float *a, float *b, float *c) {
  int i;
  for (i = 0; i < 4; i++) c[i] = 0.0;
  for (i = 0; i < 4; i++) {
    c[0] += a[i] * b[i];
    c[1] += a[i + 4] * b[i + 4];
    c[2] += a[i + 8] * b[i + 8];
    c[3] += a[i + 12] * b[i + 12];
  }
}