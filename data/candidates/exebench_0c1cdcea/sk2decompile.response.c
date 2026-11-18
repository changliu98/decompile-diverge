void TriggsM(double *x, double *M) {
  double x1 = x[0];
  double x2 = x[1];
  double x3 = x[2];
  double den = 1.0 / ((1.0 - x3 - x2 - x1) * (x3 + x1 - x2 + 1.0) *
                      (x3 * x1 + x2 + 1.0));
  M[0] = den * (1.0 - x3 - x2 + x1 * x1);
  M[1] = den * (x3 + x1) * (x3 * x1 + x2);
  M[2] = den * x1 * (x3 + x2);
  M[3] = den * (x3 + x2);
  M[4] = -den * (x2 - 1.0) * (x3 * x1 + x2);
  M[5] = -den * x1 * (x3 * x1 + x2 * x2 + x2 - 1.0);
  M[6] = den * (x3 * x3 + x3 * x2 + x2 + 1.0);
  M[7] = den * (-x1 * x1 * x1 - x1 * x3 * x3 + x1 * x2 + x3 * x2 + x2 * x2 + x1);
  M[8] = den * x1 * (x3 + x2);
}