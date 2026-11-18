void __cdecl eeval(double X, double A, double B, double C, double D, 
                   double *pQ, double *pdQ, double *pB1, double *pC2)
{
  // Intermediate values for Horner's method
  double B1 = A * X + B;       // Evaluates to: A*x + B
  double C2 = B1 * X + C;      // Evaluates to: A*x^2 + B*x + C

  // Output the polynomial value: P(x) = (A*x^2 + B*x + C)*x + D
  *pQ  = C2 * X + D;

  // Output the derivative value: P'(x) = (A*x + B1)*x + C2
  // Mathematically equivalent to: 3*A*x^2 + 2*B*x + C
  *pdQ = (A * X + B1) * X + C2;

  // Output the intermediate states
  *pB1 = B1;
  *pC2 = C2;
}