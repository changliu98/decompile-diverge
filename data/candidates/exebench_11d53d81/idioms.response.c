void eeval(double x, double a, double b, double c, double d, double *q, double *dq, double *b1, double *c2)
{
  double b1; double c2;
  b1 = a * x + b;
  c2 = b1 * x + c;
  *q = c2 * x + d;
  *dq = b1 * x * x + c2;
  *b1 = b1;
  *c2 = c2;
  return;
}