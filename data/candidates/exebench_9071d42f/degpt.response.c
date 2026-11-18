void cmul(double *aa,double *bb)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double ii;
  double rr;
  double *bb_local;
  double *aa_local;
  
  dVar1 = *aa;
  dVar2 = bb[1];
  dVar3 = *bb;
  *aa = *aa * *bb + -(aa[1] * bb[1]);
  aa[1] = dVar1 * dVar2 + aa[1] * dVar3;
  return;
}