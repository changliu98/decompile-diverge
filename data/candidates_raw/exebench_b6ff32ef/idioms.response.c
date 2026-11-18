void fmat_mul(float *a, float *b)
{
  float tmp1; float tmp2; float tmp3;
  tmp1 = a[0]*b[0] + a[1]*b[3];
  tmp2 = a[2]*b[0] + a[3]*b[3];
  tmp3 = a[4]*b[0] + a[5]*b[3] + b[4];
  a[1] = a[0]*b[1] + a[1]*b[4];
  a[3] = a[2]*b[1] + a[3]*b[4];
  a[5] = a[4]*b[1] + a[5]*b[4] + b[5];
  a[0] = tmp1;
  a[2] = tmp2;
  a[4] = tmp3;
}