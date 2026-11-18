void FindDivDiff5Coeff1(double x0, double x1, double x2, double *coeff) {
  double a, b, c;
  a = 1.0 / (x1 - x0);
  b = 1.0 / (x2 - x0);
  c = 1.0 / (x2 - x1);
  coeff[1] = a * a * b * b;
  coeff[0] = 2.0 * (a + b) * coeff[1];
  coeff[3] = c * c * a * a;
  coeff[2] = 2.0 * (c - a) * coeff[3];
  coeff[5] = c * c * b * b;
  coeff[4] = -2.0 * (c + b) * coeff[5];
}