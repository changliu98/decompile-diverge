void complexMultiplicationRI(double *a, double *b, double c, double d, double e,
                             double f) {
  *a = c * e - d * f;
  *b = c * f + d * e;
}