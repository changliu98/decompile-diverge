void dswap(double *pa,double *pb)

{
  double dVar1;
  double temp;
  double *pb_local;
  double *pa_local;
  
  dVar1 = *pa;
  *pa = *pb;
  *pb = dVar1;
  return;
}