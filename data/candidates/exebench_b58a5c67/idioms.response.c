void r2d(double *ra, double *dec, int *ih, double *am, char *isgn, int *id, double *amin)
{
  double hours = *ra / (4.0 * atan(1.0)) / 12.0;
  while (hours > 24.0)
    hours -= 24.0;
  *ih = (int) hours;
  *am = (hours - (double)(int) hours) * 60.0;
  *am += 1e-6;
  if (*am >= 60.0) {
    *am -= 60.0;
    (*ih)++;
  }
  if (*ih >= 24)
    *ih -= 24;
  if (*dec < 0.0) {
    *isgn = '-';
    *dec = - *dec;
  }
  else
    *isgn = '+';
  hours = *dec / (4.0 * atan(1.0));
  *id = (int) hours;
  *amin = (hours - (double)(int) hours) * 60.0;
  return;
}