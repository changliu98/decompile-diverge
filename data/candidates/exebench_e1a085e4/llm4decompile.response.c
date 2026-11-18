void
babl_matrix_to_float (const double *in, float *out)
{
 for (int i = 0; i < 9; i++)
  out[i] = (float)in[i];
}