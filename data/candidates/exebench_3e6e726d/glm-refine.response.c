void __cdecl mat3f_from_mat3d(float *dest, const double *src)
{
  for (int i = 0; i < 9; ++i)
  {
    dest[i] = (float)src[i];
  }
}