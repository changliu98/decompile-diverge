double __cdecl my_modf(double x, double *iptr)
{
  double x_orig = x;
  double scale = 1.0;
  int i;
  long int_part;

  // Scale down `x` until it fits within the range of a 32-bit integer.
  // This loop effectively finds the most significant digit of the integer part.
  for (i = 0; i < 100; ++i)
  {
    int_part = (int)x;
    
    // Check if x is within the valid range for a 32-bit signed integer [-2^31, 2^31 - 1]
    // Equivalent to: (x >= int_part - 1.0) && (x <= int_part + 1.0)
    if (x + 1.0 >= (double)int_part && (double)int_part >= x - 1.0)
      break;
      
    x *= 0.1;
    scale *= 10.0;
  }

  // If the number is too large to fit in a 32-bit integer even after 100 scaling iterations,
  // treat it as having no fractional part.
  if (i == 100)
  {
    *iptr = 0.0;
    return 0.0;
  }
  
  // If scaling was required (i.e., the original number was large)
  if (i > 0)
  {
    double inner_int_part;
    double frac_part;
    
    // Extract the remaining fractional part by recursively calling my_modf 
    // on the remainder after subtracting the extracted integer portion.
    double remainder = x_orig - (double)int_part * scale;
    frac_part = my_modf(remainder, &inner_int_part);
    
    // Combine the extracted integer part with the inner integer part
    *iptr = (double)int_part * scale + inner_int_part;
    return frac_part;
  }
  else
  {
    // If no scaling was needed (x was already small enough to fit in an int)
    *iptr = (double)int_part;
    return x - *iptr;
  }
}