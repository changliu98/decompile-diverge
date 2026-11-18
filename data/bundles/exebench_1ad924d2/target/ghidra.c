void pinvJ(double a,double b,double c,double d,double e,double *pJ)

{
  double dVar1;
  double dVar2;
  double dVar3;
  int i;
  double N;
  double Q;
  double de;
  double ab;
  double c2pd2;
  double e2;
  double d2;
  double c2;
  double b2;
  double a2;
  double *pJ_local;
  double e_local;
  double d_local;
  double c_local;
  double b_local;
  double a_local;
  
  dVar2 = c * c;
  dVar3 = dVar2 + d * d;
  *pJ = -b * d * e + a * (dVar2 + e * e);
  pJ[1] = b * dVar3 + -(a * d * e);
  pJ[2] = c * (dVar3 + e * e);
  pJ[3] = -c * (a * d + b * e);
  pJ[4] = d * (b * b + dVar2) + -(a * b * e);
  pJ[5] = -(a * b) * d + e * (a * a + dVar2);
  pJ[6] = pJ[3];
  pJ[7] = c * (a * a + b * b + dVar2);
  dVar2 = *pJ;
  dVar3 = pJ[1];
  dVar1 = pJ[2];
  for (i = 0; i < 8; i = i + 1) {
    pJ[i] = pJ[i] / (c * dVar1 + a * dVar2 + b * dVar3);
  }
  return;
}