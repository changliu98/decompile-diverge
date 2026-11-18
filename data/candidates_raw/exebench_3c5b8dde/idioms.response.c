void copy_mat(double *dest, float *src)
{
  int i;
  for (i = 0; i < 9; i++)
    dest[i] = src[i];
}