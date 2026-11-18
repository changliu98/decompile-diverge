void matrix_vector(float *res, float *mat, float *vec)
{
  res[0] = (mat[0] * vec[0]) + (mat[1] * vec[1]) + (mat[2] * vec[2]) + mat[3];
  res[1] = (mat[4] * vec[0]) + (mat[5] * vec[1]) + (mat[6] * vec[2]) + mat[7];
  res[2] = (mat[8] * vec[0]) + (mat[9] * vec[1]) + (mat[10] * vec[2]) + mat[11];
}