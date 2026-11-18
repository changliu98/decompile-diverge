void complexMultiplication(double a, double b, double c, double d, double *x,
                           double *y) {
  *x = a * c - b * d;
  *y = a * d + b * c;
}