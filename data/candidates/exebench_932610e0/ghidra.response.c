double randlc(double *x,double *a)

{
  ulong uVar1;
  double dVar2;
  double d2m46;
  longlong i246m1;
  double randlc;
  longlong La;
  longlong Lx;
  double *a_local;
  double *x_local;
  
  uVar1 = (long)*x * (long)*a & 0x3fffffffffff;
  dVar2 = DAT_00102008 * (double)uVar1;
  *x = (double)uVar1;
  return dVar2;
}