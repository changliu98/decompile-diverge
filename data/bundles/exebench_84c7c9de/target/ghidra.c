void geom_cross3d(double *a,double *b,double *result)

{
  double *result_local;
  double *b_local;
  double *a_local;
  
  *result = a[1] * b[2] + -(a[2] * b[1]);
  result[1] = a[2] * *b + -(*a * b[2]);
  result[2] = *a * b[1] + -(a[1] * *b);
  return;
}