void eeval(double X,double A,double B,double C,double D,double *pQ,double *pdQ,double *pB1,
          double *pC2)

{
  double dVar1;
  double dVar2;
  double Q;
  double dQ;
  double C2;
  double B1;
  double q0;
  double *pC2_local;
  double *pB1_local;
  double *pdQ_local;
  double *pQ_local;
  double D_local;
  double C_local;
  double B_local;
  double A_local;
  double X_local;
  
  dVar1 = A * X + B;
  dVar2 = dVar1 * X + C;
  *pQ = dVar2 * X + D;
  *pdQ = (A * X + dVar1) * X + dVar2;
  *pB1 = dVar1;
  *pC2 = dVar2;
  return;
}