void dot_matrixT_vector_did(double *matrix,long *in,double *out)

{
  double *out_local;
  long *in_local;
  double *matrix_local;
  
  *out = matrix[6] * (double)in[2] + *matrix * (double)*in + matrix[3] * (double)in[1];
  out[1] = matrix[7] * (double)in[2] + matrix[1] * (double)*in + matrix[4] * (double)in[1];
  out[2] = matrix[8] * (double)in[2] + matrix[2] * (double)*in + matrix[5] * (double)in[1];
  return;
}