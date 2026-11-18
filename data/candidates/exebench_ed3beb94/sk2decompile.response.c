void math_matrix_copy(float *src, float *dst) {
  int i;
  for (i = 0; i < 16; i++) {
    dst[i] = src[i];
  }
}