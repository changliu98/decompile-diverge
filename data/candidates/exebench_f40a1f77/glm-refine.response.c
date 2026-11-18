void __cdecl get_bits_exp(double x, double *a, int *n)
{
  double t2;
  unsigned __int64 x_bits = *(unsigned __int64 *)&x;
  unsigned __int64 exp_bits = x_bits & 0x7FF0000000000000ULL;

  if (x_bits != 0)
  {
    // Normal or infinity/NaN case
    *n = (int)(exp_bits >> 52) - 1023;
    t2 = *(double *)&exp_bits;
  }
  else
  {
    // Zero or subnormal case
    // Multiply by 2^60 to normalize the subnormal number
    double scaled_x = *(double *)&LODWORD(x) * 1152921504606846976.0; // 2^60
    
    unsigned __int64 scaled_exp_bits = *(unsigned __int64 *)&scaled_x & 0x7FF0000000000000ULL;
    *n = (int)(scaled_exp_bits >> 52) - 1083; // 1023 - 60 = 963, so - 1023 - 60 = -1083
    
    t2 = *(double *)&scaled_exp_bits;
  }
  
  *a = x / t2;
}