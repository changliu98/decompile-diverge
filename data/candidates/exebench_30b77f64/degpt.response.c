void computeVariables(double voltage, double *state_values, double *rate_values, double *computed_vars)
{
  // Calculate the first variable by multiplying voi with a constant
  *computed_vars = DAT_00102010 * voltage;
  // Calculate the second variable by multiplying the first variable with another constant
  computed_vars[1] = DAT_00102008 * *computed_vars;
}