void mat3f_from_mat3d(float *m3f, const double *m3d) {
  int i;
  for (i = 0; i < 9; i++) {
    m3f[i] = (float)m3d[i];
  }
}