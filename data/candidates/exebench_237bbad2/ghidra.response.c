int shape_tria6(double *L,double *N)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double L3;
  double L2;
  double L1;
  double *N_local;
  double *L_local;
  
  dVar1 = *L;
  dVar2 = L[1];
  dVar3 = (DAT_00102018 - dVar1) - dVar2;
  *N = dVar1 * (dVar1 + dVar1 + DAT_00102010);
  N[1] = DAT_00102008 * dVar1 * dVar2;
  N[2] = dVar2 * (dVar2 + dVar2 + DAT_00102010);
  N[3] = DAT_00102008 * dVar2 * dVar3;
  N[4] = dVar3 * (dVar3 + dVar3 + DAT_00102010);
  N[5] = DAT_00102008 * dVar1 * dVar3;
  return 0;
}