void addthe(double C1,double S1,double C2,double S2,double *C,double *S)

{
  double *S_local;
  double *C_local;
  double S2_local;
  double C2_local;
  double S1_local;
  double C1_local;
  
  *C = C1 * C2 + -(S1 * S2);
  *S = S1 * C2 + C1 * S2;
  return;
}