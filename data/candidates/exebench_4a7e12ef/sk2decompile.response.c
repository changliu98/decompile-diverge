void mat3mulv(float *c, float *a, float *b) {
  int i, j;
  float sum;
  for (j = 0; j < 3; j++) {
    sum = 0.0;
    for (i = 0; i < 3; i++) {
      sum += a[j * 3 + i] * b[i];
    }
    c[j] = sum;
  }
}