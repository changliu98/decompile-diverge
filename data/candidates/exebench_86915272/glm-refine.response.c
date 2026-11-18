void __cdecl rahms(double ra, int *h, int *m, float *s)
{
  // Normalize the right ascension (ra) to the range [0.0, 360.0)
  if (ra < 0.0)
    ra += 360.0;
  else if (ra >= 360.0)
    ra -= 360.0;

  // Convert degrees to hours (360 degrees = 24 hours, so 1 hour = 15 degrees)
  double hours = ra / 15.0;

  // Extract hours
  *h = (int)hours;

  // Extract minutes from the fractional part of hours
  double minutes = 60.0 * (hours - (double)*h);
  *m = (int)minutes;

  // Extract seconds from the fractional part of minutes
  *s = (float)(60.0 * (minutes - (double)*m));
}