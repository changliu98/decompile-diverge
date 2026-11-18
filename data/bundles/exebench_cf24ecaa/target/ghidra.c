void dot_matrixT_vector_ddd(double *matrix,double *in,double *out)

{
  double *out_local;
  double *in_local;
  double *matrix_local;
  
  *out = matrix[6] * in[2] + *matrix * *in + matrix[3] * in[1];
  out[1] = matrix[7] * in[2] + matrix[1] * *in + matrix[4] * in[1];
  out[2] = matrix[8] * in[2] + matrix[2] * *in + matrix[5] * in[1];
  return;
}