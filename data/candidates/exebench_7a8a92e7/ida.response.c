void __cdecl dot_matrixT_vector_did(double *matrix, long *in, double *out)
{
  *out = matrix[6] * (double)(int)in[2] + *matrix * (double)(int)*in + matrix[3] * (double)(int)in[1];
  out[1] = matrix[7] * (double)(int)in[2] + matrix[1] * (double)(int)*in + matrix[4] * (double)(int)in[1];
  out[2] = matrix[8] * (double)(int)in[2] + matrix[2] * (double)(int)*in + matrix[5] * (double)(int)in[1];
}