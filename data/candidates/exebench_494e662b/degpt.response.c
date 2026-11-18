void denormF(double *F,double *A1,double *A2)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double y;
  double x;
  double r;
  double *A2_local;
  double *A1_local;
  double *F_local;
  
  dVar1 = *A2;
  dVar2 = A2[1];
  dVar3 = A2[2];
  F[6] = dVar2 * *F + dVar3 * F[3] + F[6];
  F[7] = dVar2 * F[1] + dVar3 * F[4] + F[7];
  F[8] = dVar2 * F[2] + dVar3 * F[5] + F[8];
  *F = dVar1 * *F;
  F[1] = dVar1 * F[1];
  F[2] = dVar1 * F[2];
  F[3] = dVar1 * F[3];
  F[4] = dVar1 * F[4];
  F[5] = dVar1 * F[5];
  dVar1 = *A1;
  dVar2 = A1[1];
  dVar3 = A1[2];
  F[2] = dVar2 * *F + dVar3 * F[1] + F[2];
  F[5] = dVar2 * F[3] + dVar3 * F[4] + F[5];
  F[8] = dVar2 * F[6] + dVar3 * F[7] + F[8];
  *F = dVar1 * *F;
  F[3] = dVar1 * F[3];
  F[6] = dVar1 * F[6];
  F[1] = dVar1 * F[1];
  F[4] = dVar1 * F[4];
  F[7] = dVar1 * F[7];
  return;
}