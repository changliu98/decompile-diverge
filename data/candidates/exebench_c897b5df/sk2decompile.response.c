void mlVectorScaleTo(const float *a, float s, float *b) {
  unsigned int i;
  for (i = 0; i < 3; i++) {
    b[i] = a[i] * s;
  }
}