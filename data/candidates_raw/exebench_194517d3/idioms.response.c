void f_matvec(float *a, float *b, float *c)
{
  c[0] = a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  c[1] = a[3]*b[0] + a[4]*b[1] + a[5]*b[2];
  c[2] = a[6]*b[0] + a[7]*b[1] + a[8]*b[2];
}