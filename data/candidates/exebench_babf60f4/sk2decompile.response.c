void matmult(float *a, float *b, float *c) {
  int i, j, k;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      c[j * 4 + i] = 0.0;
      for (k = 0; k < 4; k++) {
        c[j * 4 + i] += a[k * 4 + i] * b[j * 4 + k];
      }
    }
  }
}