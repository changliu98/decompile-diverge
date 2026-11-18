double randlc(double *x,double a)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double r;
  double z;
  double x2;
  double x1;
  double a2;
  double a1;
  double t4;
  double t3;
  double t2;
  double t1;
  double t46;
  double t23;
  double r46;
  double r23;
  double a_local;
  double *x_local;
  
  dVar1 = (double)(int)(DAT_00102028 * a) * DAT_00102020 + a;
  dVar2 = (double)(int)(DAT_00102028 * *x) * DAT_00102020 + *x;
  dVar3 = (double)(int)(DAT_00102028 * a) * dVar2 + dVar1 * (double)(int)(DAT_00102028 * *x);
  dVar1 = ((double)(int)(DAT_00102028 * dVar3) * DAT_00102020 + dVar3) * DAT_00102018 +
          dVar1 * dVar2;
  *x = (double)(int)(DAT_00102008 * dVar1) * DAT_00102010 + dVar1;
  return DAT_00102008 * *x;
}