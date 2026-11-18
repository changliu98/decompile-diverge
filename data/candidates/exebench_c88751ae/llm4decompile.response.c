int hmsra(int h, int m, float s, double *ra)
{
  int stat;

  *ra = (double)h + (double)m/60.0 + s/3600.0;
  *ra *= 15.0;

  if (*ra < 0.0) stat = 1;
  else if (*ra > 360.0) stat = 1;
  else stat = 0;

  return(stat);
}