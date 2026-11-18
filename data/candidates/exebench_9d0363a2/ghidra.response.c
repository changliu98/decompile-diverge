void ccp4_dcross(double *a,double *b,double *c)

{
  double *c_local;
  double *b_local;
  double *a_local;
  
  *c = a[1] * b[2] + -(b[1] * a[2]);
  c[1] = a[2] * *b + -(b[2] * *a);
  c[2] = *a * b[1] + -(*b * a[1]);
  return;
}