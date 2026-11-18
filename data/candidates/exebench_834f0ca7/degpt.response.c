void FindDivDiff5Coeff1(double a,double b,double c,double *dd)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double cb;
  double ca;
  double ba;
  double *dd_local;
  double c_local;
  double b_local;
  double a_local;
  
  dVar1 = DAT_00102020 / (b - a);
  dVar2 = DAT_00102020 / (c - a);
  dVar3 = DAT_00102020 / (c - b);
  dd[1] = dVar1 * dVar1 * dVar2 * dVar2;
  *dd = DAT_00102018 * (dVar2 + dVar1) * dd[1];
  dd[3] = dVar3 * dVar3 * dVar1 * dVar1;
  dd[2] = DAT_00102018 * (dVar3 - dVar1) * dd[3];
  dd[5] = dVar3 * dVar3 * dVar2 * dVar2;
  dd[4] = DAT_00102010 * (dVar3 + dVar2) * dd[5];
  return;
}