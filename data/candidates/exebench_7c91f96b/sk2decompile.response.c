void mm_us(float *a, float *b, float *c) {
  int i, j, k;
  float sum;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      sum = 0.0;
      for (k = 0; k < 4; k++) {
        sum += a[i * 4 + k] * b[k * 4 + j];
      }
      c[i * 4 + j] = sum;
    }
  }
}