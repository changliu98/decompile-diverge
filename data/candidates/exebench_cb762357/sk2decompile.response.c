void scale_mat(int *mat, int x, int y) {
  if (x != 1024) {
    mat[0] = mat[0] * x / 1024;
    mat[2] = mat[2] * x / 1024;
    mat[4] = mat[4] * x / 1024;
  }
  if (y != 1024) {
    mat[1] = mat[1] * y / 1024;
    mat[3] = mat[3] * y / 1024;
    mat[5] = mat[5] * y / 1024;
  }
}