void eeval(double x, double a, double b, double c, double d, double *y,
           double *dy, double *da, double *db) {
  double p, q;
  p = a * x + b;
  q = p * x + c;
  *y = q * x + d;
  *dy = q + p * x;
  *da = p;
  *db = q;
}