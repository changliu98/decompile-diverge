void __cdecl computeRates(double voi, double *states, double *rates, double *variables)
{
  // The XOR operation with 0x8000000000000000 flips the sign bit of the IEEE 754 double.
  // This is functionally equivalent to negating the double value.
  // The `* 1.0` operations are no-ops and can be safely omitted for clarity.
  
  rates[0] = -states[1];
  rates[1] =  states[0];
}