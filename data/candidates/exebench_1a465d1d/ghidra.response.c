void FindDivDiff5Coeff2(double a,double b,double c,double d,double *dd)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dc;
  double db;
  double da;
  double cb;
  double ca;
  double ba;
  double *dd_local;
  double d_local;
  double c_local;
  double b_local;
  double a_local;
  
  dVar1 = DAT_00102010 / (b - a);
  dVar2 = DAT_00102010 / (c - a);
  dVar3 = DAT_00102010 / (c - b);
  dVar4 = DAT_00102010 / (d - a);
  dVar5 = DAT_00102010 / (d - b);
  dVar6 = DAT_00102010 / (d - c);
  *dd = -dVar1 * dVar1 * dVar2 * dVar2 * dVar4;
  dd[1] = -((dVar3 + dVar3 + dVar5) - dVar1) * dVar1 * dVar5 * dVar3 * dVar3;
  dd[2] = -dVar1 * dVar5 * dVar3 * dVar3;
  dd[3] = -((dVar6 - (dVar3 + dVar3)) - dVar2) * dVar6 * dVar2 * dVar3 * dVar3;
  dd[4] = -dVar6 * dVar2 * dVar3 * dVar3;
  dd[5] = dVar4 * dVar5 * dVar5 * dVar6 * dVar6;
  return;
}