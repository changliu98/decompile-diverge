void dual_mul(double a, double b, double c, double d, double *x, double *y) {
  *x = a * c;
  *y = a * d + b * c;
}