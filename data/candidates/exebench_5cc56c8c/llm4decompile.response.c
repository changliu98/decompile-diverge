void computeRates(double voi, double *states, double *rates, double *variables)
{
    rates[0] = -1.0 * states[1];
    rates[1] = 1.0 * states[0];
}