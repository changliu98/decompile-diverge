void f2(double *x, double *y)
{
  x[0] -= y[0];
  y[0] += x[0];
  x[0] = y[0] - x[0];
}