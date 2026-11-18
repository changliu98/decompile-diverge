int matMultMV(double *mat, double *vec, double *out) {
  double x, y, z;
  x = mat[0] * vec[0] + mat[1] * vec[1] + mat[2] * vec[2] + mat[3] * vec[3];
  y = mat[4] * vec[0] + mat[5] * vec[1] + mat[6] * vec[2] + mat[7] * vec[3];
  z = mat[8] * vec[0] + mat[9] * vec[1] + mat[10] * vec[2] + mat[11] * vec[3];
  out[0] = mat[12] * vec[0] + mat[13] * vec[1] + mat[14] * vec[2] +
           mat[15] * vec[3];
  out[1] = x;
  out[2] = y;
  out[3] = z;
  return 0;
}