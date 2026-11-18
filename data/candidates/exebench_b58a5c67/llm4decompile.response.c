void r2d(double *ra, double *dec, int *ih, double *am, char *isgn, int *id,
 double *amin)
{
 float ra2, dec2;

 ra2 = *ra / 15.0 / 0.0174532925199433;
 while (ra2 > 24.0)
  ra2 -= 24.0;
 *ih = (int) ra2;
 *am = (ra2 - (float) *ih) * 60.0;
 *am += 0.5;
 if (*am >= 60.0) {
  *am -= 60.0;
  *ih += 1;
 }
 if (*ih >= 24)
  *ih -= 24;

 if (*dec < 0.0) {
  *isgn = '-';
  *dec = -*dec;
 } else
  *isgn = '+';
 dec2 = *dec / 0.0174532925199433;
 *id = (int) dec2;
 *amin = (dec2 - (float) *id) * 60.0;
}