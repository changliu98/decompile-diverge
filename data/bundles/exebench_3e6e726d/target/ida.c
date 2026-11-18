void __cdecl mat3f_from_mat3d(float *dest, const double *src)
{
  float v2; // xmm0_4
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 9; ++i )
  {
    v2 = src[i];
    dest[i] = v2;
  }
}