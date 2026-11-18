double ran1(long *idum)
{
  int j;
  long k;
  static long ran1_iv[32];
  static long ran1_iy = 0;
  if (*idum <= 0 || !ran1_iy) {
    if (- *idum >= 1)
      *idum = - *idum;
    else
      *idum = 1;
    for (j=32 -1; j>=0; j--) {
      *idum = *idum * 16807 % 127773;
      if (j < 2)
        ran1_iv[j] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }
  k = (*idum / 127773);
  *idum = 16807 * (*idum - k * 127773) - 2836 * k;
  if (*idum < 0)
    *idum += 2147483647;
  j = ran1_iy / 127773;
  ran1_iy = ran1_iv[j];
  ran1_iv[j] = *idum;
  return ran1_iy * 4.656612875245797e-10;
}