void __cdecl decdms(double dec, int *d, int *m, float *s)
{
  // Extract the integer degrees
  *d = (int)dec;

  // Calculate the fractional part of the degree
  double frac_deg = dec - (double)*d;

  // Take the absolute value of the fractional part
  if (frac_deg < 0.0)
    frac_deg = -frac_deg;

  // Convert the fractional degrees to minutes
  double min = 60.0 * frac_deg;
  *m = (int)min;

  // Convert the fractional minutes to seconds
  double frac_min = min - (double)*m;
  *s = (float)(60.0 * frac_min);
}