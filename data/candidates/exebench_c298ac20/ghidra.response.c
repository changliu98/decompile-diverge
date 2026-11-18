void swap(double *a,double *b)

{
  double dVar1;
  double t;
  double *b_local;
  double *a_local;
  
  dVar1 = *a;
  *a = *b;
  *b = dVar1;
  return;
}