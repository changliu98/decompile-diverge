void mlVectorSub(float *a, float *b) {
  unsigned int i;
  for (i = 0; i < 3; i++) {
    a[i] -= b[i];
  }
}