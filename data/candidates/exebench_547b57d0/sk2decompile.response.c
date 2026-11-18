void addthe(double a1, double a2, double b1, double b2, double *c1,
            double *c2) {
  double c11, c22;
  c11 = a1 * b1 - a2 * b2;
  c22 = a1 * b2 + a2 * b1;
  *c1 = c11;
  *c2 = c22;
}