void d2matvec(double *a, double *x, double *y)
{
  y[0] = a[0]*x[0] + a[1]*x[1];
  y[1] = a[2]*x[0] + a[3]*x[1];
}