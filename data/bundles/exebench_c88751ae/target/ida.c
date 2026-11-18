int __cdecl hmsra(int h, int m, float s, double *ra)
{
  *ra = (double)h + (double)m / 60.0 + s / 3600.0;
  *ra = 15.0 * *ra;
  return *ra < 0.0 || *ra > 360.0;
}