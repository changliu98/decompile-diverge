void mat3f_from_mat3d(float *dest, double *src)
{
  int i;
  for (i = 0; i < 9; i++)
    dest[i] = (float)src[i];
}