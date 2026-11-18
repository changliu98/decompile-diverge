void innerdct(double *a,double *b,double *c)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double b5;
  double b4;
  double b3;
  double b2;
  double b1;
  double b0;
  double *c_local;
  double *b_local;
  double *a_local;
  
  dVar1 = *a + a[7];
  dVar2 = a[1] + a[6];
  dVar3 = a[2] + a[5];
  dVar4 = a[3] + a[4];
  dVar5 = (dVar1 + dVar4) * c[4];
  dVar6 = (dVar2 + dVar3) * c[4];
  *b = dVar5 + dVar6;
  b[0x20] = dVar5 - dVar6;
  b[0x10] = (dVar1 - dVar4) * c[2] + (dVar2 - dVar3) * c[6];
  b[0x30] = (dVar1 - dVar4) * c[6] + (dVar3 - dVar2) * c[2];
  dVar1 = *a - a[7];
  dVar2 = a[1] - a[6];
  dVar3 = a[2] - a[5];
  dVar4 = a[3] - a[4];
  b[8] = dVar4 * c[7] + dVar3 * c[5] + dVar1 * c[1] + dVar2 * c[3];
  b[0x18] = -dVar4 * c[5] + -dVar3 * c[1] + dVar1 * c[3] + -(dVar2 * c[7]);
  b[0x28] = dVar4 * c[3] + dVar3 * c[7] + dVar1 * c[5] + -(dVar2 * c[1]);
  b[0x38] = -dVar4 * c[1] + dVar3 * c[3] + dVar1 * c[7] + -(dVar2 * c[5]);
  return;
}