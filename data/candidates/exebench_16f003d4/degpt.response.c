void calc_speed(double *x0,double *x1,double *x2,double dt)

{
  int iVar1;
  double dVar2;
  double b;
  double a;
  int k;
  int j;
  int i;
  double dt_local;
  double *x2_local;
  double *x1_local;
  double *x0_local;
  
  for (j = 0; j < 0x13; j = j + 6) {
    for (i = 0; i < 3; i = i + 1) {
      iVar1 = j + i;
      dVar2 = (x2[iVar1] + x0[iVar1]) / DAT_00102010 - x1[iVar1];
      x1[iVar1 + 3] = (dVar2 + dVar2 + (x2[iVar1] - x0[iVar1]) / DAT_00102010) / dt;
    }
  }
  return;
}