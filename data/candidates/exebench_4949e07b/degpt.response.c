void cftx020(double *a)

{
  double dVar1;
  double dVar2;
  double x0i;
  double x0r;
  double *a_local;
  
  dVar1 = *a;
  dVar2 = a[1];
  *a = a[2] + *a;
  a[1] = a[3] + a[1];
  a[2] = dVar1 - a[2];
  a[3] = dVar2 - a[3];
  return;
}