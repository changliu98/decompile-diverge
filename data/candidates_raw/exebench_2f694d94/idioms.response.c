void f_1(double t, double *y, double *dydt, double *params)
{
  double *rates = params;
  double *variables = y;
  variables[1] = rates[0];
  return;
}