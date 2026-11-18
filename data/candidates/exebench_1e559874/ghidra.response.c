void convolve_4(double *out,double *left,double *right)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double a;
  double r3;
  double r2;
  double r1;
  double r0;
  double l3;
  double l2;
  double l1;
  double l0;
  double *right_local;
  double *left_local;
  double *out_local;
  
  dVar1 = *left;
  dVar2 = *right;
  dVar3 = left[1];
  dVar4 = right[1];
  *out = dVar1 * dVar2;
  dVar5 = left[2];
  dVar6 = right[2];
  out[1] = dVar1 * dVar4 + dVar3 * dVar2;
  dVar7 = left[3];
  dVar8 = right[3];
  out[2] = dVar5 * dVar2 + dVar1 * dVar6 + dVar3 * dVar4;
  out[3] = dVar7 * dVar2 + dVar5 * dVar4 + dVar1 * dVar8 + dVar3 * dVar6;
  out[4] = dVar7 * dVar4 + dVar3 * dVar8 + dVar5 * dVar6;
  out[5] = dVar5 * dVar8 + dVar7 * dVar6;
  out[6] = dVar7 * dVar8;
  return;
}