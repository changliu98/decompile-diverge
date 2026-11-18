void fn_5(double *a,double *b,double *sum,double *prod)

{
  int i;
  double *prod_local;
  double *sum_local;
  double *b_local;
  double *a_local;
  
  for (i = 0; i < 10; i = i + 1) {
    sum[i] = a[i] * b[i];
  }
  prod[i] = a[i] * b[i];
  return;
}