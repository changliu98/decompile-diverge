void swapminusfloat(double *a,double *b)

{
  double *b_local;
  double *a_local;
  
  *a = *a - *b;
  *b = *a + *b;
  *a = *b - *a;
  return;
}