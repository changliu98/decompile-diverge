void eeval(double X, double A, double B, double C, double D,
    double *pQ, double *pdQ, double *pB1, double *pC2)
{
  double B1, C2;
  *pQ = (((A * X + B) * X + C) * X + D);
  *pdQ = ((A * X + B) * X + C) * X + C;
  *pB1 = (A * X + B);
  *pC2 = ((A * X + B) * X + C);
}