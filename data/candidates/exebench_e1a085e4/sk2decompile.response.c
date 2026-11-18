static inline void babl_matrix_to_float(const double *matrix, float *fmatrix) {
  int i;
  for (i = 0; i < 9; i++) {
    fmatrix[i] = (float)matrix[i];
  }
}