double func0(double a,int digits)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double n;
  int digits_local;
  double a_local;
  
  dVar1 = pow(DAT_00102008,(double)-digits);
  dVar2 = ceil(a / dVar1);
  dVar3 = pow(DAT_00102008,(double)digits);
  dVar1 = round(dVar2 * dVar1 * dVar3);
  dVar2 = pow(DAT_00102008,(double)digits);
  return dVar1 / dVar2;
}