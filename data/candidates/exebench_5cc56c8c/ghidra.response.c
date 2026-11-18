void computeRates(double voi,double *states,double *rates,double *variables)

{
  double *variables_local;
  double *rates_local;
  double *states_local;
  double voi_local;
  
  *rates = -states[1] * DAT_00102008;
  rates[1] = DAT_00102008 * *states;
  return;
}