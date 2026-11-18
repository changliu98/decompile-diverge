void f_1(double t, double *y, double *dydt, void *data)
{
  double *params = (double *)data;
  dydt[0] = y[0]*params[0];
  dydt[1] = y[1]*params[1];
  dydt[2] = y[2]*params[2];
}