void __cdecl computeRates(double voi, double *states, double *rates, double *variables)
{
  *rates = COERCE_DOUBLE(*((_QWORD *)states + 1) ^ 0x8000000000000000LL) * 1.0;
  rates[1] = 1.0 * *states;
}