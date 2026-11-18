void TriggsM(double *filter,double *M)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double a3;
  double a2;
  double a1;
  double scale;
  double *M_local;
  double *filter_local;
  
  dVar1 = *filter;
  dVar2 = filter[1];
  dVar3 = filter[2];
  dVar4 = DAT_00102008 /
          ((((DAT_00102008 + dVar3) - dVar2) + dVar1) * (((DAT_00102008 - dVar3) - dVar2) - dVar1) *
          ((dVar3 - dVar1) * dVar1 + DAT_00102008 + dVar2));
  *M = dVar4 * ((-dVar1 * dVar1 + -dVar1 * dVar3 + DAT_00102008) - dVar2);
  M[1] = dVar4 * (dVar1 + dVar3) * (dVar1 * dVar3 + dVar2);
  M[2] = dVar4 * dVar1 * (dVar1 * dVar2 + dVar3);
  M[3] = dVar4 * (dVar1 * dVar2 + dVar3);
  M[4] = -dVar4 * (dVar2 - DAT_00102008) * (dVar1 * dVar3 + dVar2);
  M[5] = -dVar4 * dVar1 * ((dVar1 * dVar3 + dVar1 * dVar1 + dVar2) - DAT_00102008);
  M[6] = dVar4 * (-dVar2 * dVar2 + dVar3 * dVar3 + dVar1 * dVar3 + dVar2);
  M[7] = dVar4 * (-dVar1 * dVar2 +
                  -(dVar1 * dVar1) * dVar1 +
                  -(dVar3 * dVar1) * dVar1 + dVar3 * dVar2 + dVar1 * dVar2 * dVar2 + dVar1);
  M[8] = dVar4 * dVar1 * (dVar1 * dVar2 + dVar3);
  return;
}