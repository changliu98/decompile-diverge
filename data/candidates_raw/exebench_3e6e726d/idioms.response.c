void copy_mat(float *dest, double *src)
{
  int i;
  for (i = 0; i < 9; i++)
    dest[i] = (float)src[i];
}