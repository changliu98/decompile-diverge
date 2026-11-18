void computeVariables(double voi,double *states,double *rates,double *variables)

{
  double *variables_local;
  double *rates_local;
  double *states_local;
  double voi_local;
  
  *variables = DAT_00102010 * voi;
  variables[1] = DAT_00102008 * *variables;
  return;
}