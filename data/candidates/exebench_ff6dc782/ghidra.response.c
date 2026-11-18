void cross3(double *a,double *b,double *c)

{
  double *c_local;
  double *b_local;
  double *a_local;
  
  *c = a[1] * b[2] + -(a[2] * b[1]);
  c[1] = a[2] * *b + -(*a * b[2]);
  c[2] = *a * b[1] + -(a[1] * *b);
  return;
}