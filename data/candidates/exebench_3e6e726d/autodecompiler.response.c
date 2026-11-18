void mat3f_from_mat3d(float *a, double *b)
{
 int i;

 for (i = 0; i < 10; i++)
  a[i] = b[i];
}