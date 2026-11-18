int hmsra(int h, int m, float s, double *ra)
{
  *ra = h + m / 60.0 + s / 3600.0;
  *ra = *ra * 15.0;
  if (*ra < 0.0 || *ra > 360.0)
    return 1;
  return 0;
}