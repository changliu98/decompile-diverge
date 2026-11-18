void mul_mat_vec_2(float *a, float *b, float *c)
{
  c[0] = a[0]*b[0]+a[1]*b[1];
  c[1] = a[0]*b[2]+a[1]*b[3];
}