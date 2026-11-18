void __cdecl r2d(double *ra, double *dec, int *ih, double *am, char *isgn, int *id, double *amin)
{
  float hours;
  float degrees;

  // Convert Right Ascension from radians to hours (1 hour = 15 degrees)
  hours = (float)(*ra / 0.017453292 / 15.0);
  
  // Normalize hours to [0.0, 24.0) range
  while (hours >= 24.0f)
    hours -= 24.0f;

  // Extract integer hours and fractional minutes
  *ih = (int)hours;
  *am = (float)(hours - (int)hours) * 60.0f;
  
  // Add a tiny epsilon to handle floating-point inaccuracies
  *am = *am + 0.000001f;
  
  // Handle overflow of minutes
  if (*am >= 60.0f)
  {
    *am -= 60.0f;
    ++*ih;
  }
  
  // Normalize hours again after overflow
  if (*ih >= 24)
    *ih -= 24;

  // Determine sign of Declination
  if (*dec >= 0.0)
  {
    *isgn = '+'; // ASCII 43
  }
  else
  {
    *isgn = '-'; // ASCII 45
    // Equivalent to *dec = -*dec; (flips the sign bit of the double)
    *dec = -*dec; 
  }

  // Convert Declination from radians to degrees
  degrees = (float)(*dec / 0.017453292);
  
  // Extract integer degrees and fractional minutes
  *id = (int)degrees;
  *amin = (float)(degrees - (float)*id) * 60.0f;
}