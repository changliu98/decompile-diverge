void __cdecl computeVariables(double voi, double *states, double *rates, double *variables)
{
  *variables = 2.0 * voi;
  variables[1] = 3.0 * *variables;
}