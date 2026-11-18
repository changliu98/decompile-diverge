void swi_coortrf2(double *xp, double *retp, double seps, double ceps)
{
  double x[3], y[3];
  int i;
  for (i = 0; i <= 2; i++)
    x[i] = xp[i];
  y[0] = x[0];
  y[1] = x[1] * ceps + x[2] * seps;
  y[2] = -x[1] * seps + x[2] * ceps;
  for (i = 0; i <= 2; i++)
    retp[i] = y[i];
}