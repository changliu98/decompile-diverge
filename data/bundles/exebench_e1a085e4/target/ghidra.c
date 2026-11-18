void babl_matrix_to_float(double *in,float *out)

{
  int i;
  float *out_local;
  double *in_local;
  
  for (i = 0; i < 9; i = i + 1) {
    out[i] = (float)in[i];
  }
  return;
}