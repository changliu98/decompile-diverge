void swi_coortrf2(double *xpo, double *xpn, double sineps, double coseps)
{
  double x[3];
  x[0] = xpo[0];
  x[1] = xpo[1] * coseps + xpo[2] * sineps;
  x[2] = -xpo[1] * sineps + xpo[2] * coseps;
  xpn[0] = x[0];
  xpn[1] = x[1];
  xpn[2] = x[2];
}