void mat3d_from_mat3f(double *dest, float *src)
{
  int i;
  for (i = 0; i < 9; i++)
    dest[i] = src[i];
}