float dot(float *a, float *b, size_t len) {
  int i;
  float sum = 0.0;
  for (i = 0; i < len; i++) {
    sum += a[i] * b[i];
  }
  return sum;
}