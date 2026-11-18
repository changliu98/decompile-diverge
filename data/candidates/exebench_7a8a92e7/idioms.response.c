void dot_matrixT_vector_did(double *mat, long *in, long *out)
{
  out[0] = mat[0] * in[0] + mat[3] * in[1] + mat[6] * in[2];
  out[1] = mat[1] * in[0] + mat[4] * in[1] + mat[7] * in[2];
  out[2] = mat[2] * in[0] + mat[5] * in[1] + mat[8] * in[2];
}