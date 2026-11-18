void __cdecl eeval(double X, double A, double B, double C, double D, double *pQ, double *pdQ, double *pB1, double *pC2)
{
  double C2; // [rsp+10h] [rbp-60h]
  double B1; // [rsp+18h] [rbp-58h]

  B1 = A * X + B;
  C2 = B1 * X + C;
  *pQ = C2 * X + D;
  *pdQ = (A * X + B1) * X + C2;
  *pB1 = B1;
  *pC2 = C2;
}