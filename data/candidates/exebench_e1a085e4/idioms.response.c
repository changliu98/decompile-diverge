void babl_matrix_to_float(double in[9], float out[9])
{
  int i;
  for (i = 0; i < 9; i++)
    out[i] = (float)in[i];
}