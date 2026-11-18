void mat3d_from_mat3f(double *dst, const float *src) {
  int i;
  for (i = 0; i < 9; i++) {
    dst[i] = src[i];
  }
}