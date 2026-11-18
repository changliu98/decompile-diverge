int __cdecl zuchk_(double *yr, double *yi, int *nz, double *ascle, double *tol)
{
  double abs_yr;
  double abs_yi;
  double min_abs;
  double max_abs;

  *nz = 0;
  
  // The bitwise XOR with 0x8000000000000000LL on a double is a standard compiler 
  // optimization for calculating the absolute value (fabs). 
  // We restore it to its mathematical equivalent for readability.
  abs_yr = fabs(*yr);
  abs_yi = fabs(*yi);

  // Determine the minimum and maximum of the two absolute values
  if (abs_yi < abs_yr)
  {
    min_abs = abs_yi;
    max_abs = abs_yr;
  }
  else
  {
    min_abs = abs_yr;
    max_abs = abs_yi;
  }

  // Check if the smaller magnitude is within the allowed underflow limit 'ascle'
  if (min_abs <= *ascle)
  {
    // If the ratio of the smallest to the largest magnitude is greater than 
    // the tolerance 'tol', set the underflow flag *nz to 1.
    // (Note: Division is used instead of multiplication to avoid potential 
    // overflow/underflow issues, matching the original assembly behavior).
    if (min_abs / *tol > max_abs)
    {
      *nz = 1;
    }
  }

  return 0;
}