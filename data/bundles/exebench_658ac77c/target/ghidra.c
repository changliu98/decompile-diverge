void vertexAdd(double *a,double *b,double *out)

{
  double *out_local;
  double *b_local;
  double *a_local;
  
  *out = *a + *b;
  out[1] = a[1] + b[1];
  out[2] = a[2] + b[2];
  return;
}