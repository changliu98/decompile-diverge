void __cdecl babl_matrix_to_float(const double *in, float *out)
{
  float v2; // xmm0_4
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 9; ++i )
  {
    v2 = in[i];
    out[i] = v2;
  }
}