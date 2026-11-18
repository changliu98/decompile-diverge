void __cdecl mat3d_from_mat3f(double *dest, const float *src)
{
  int i; // [rsp+0h] [rbp-14h]

  for ( i = 0; i < 9; ++i )
    dest[i] = src[i];
}