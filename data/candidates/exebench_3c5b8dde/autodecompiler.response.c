void mat3d_from_mat3f(double *a, float *b)
{
 int i;
 for(i=0;i<10;i++)
 {
  a[i] = b[i];
 }
}