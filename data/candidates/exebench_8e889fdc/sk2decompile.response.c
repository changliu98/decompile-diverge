void load_scl_mat(float *mat, float x, float y, float z) {
  mat[0] = x;
  mat[4] = 0.0;
  mat[8] = 0.0;
  mat[12] = 0.0;
  mat[1] = 0.0;
  mat[5] = y;
  mat[9] = 0.0;
  mat[13] = 0.0;
  mat[2] = 0.0;
  mat[6] = 0.0;
  mat[10] = z;
  mat[14] = 0.0;
  mat[3] = 0.0;
  mat[7] = 0.0;
  mat[11] = 0.0;
  mat[15] = 1.0;
}