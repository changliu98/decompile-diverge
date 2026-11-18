float ran1(long *idum)
{
  int j;
  long k;
  static long ran1_iv[32];
  static long ran1_iy = 0;
  float temp;
  if (*idum <= 0 || !ran1_iy) {
    if (- *idum >= 1)
      *idum = - *idum;
    else
      *idum = 1;
    for (j = 32 + 1; j >= 0; j--) {
      k = *idum / 127773;
      *idum = 16807 * (*idum - k * 127773) - 2836 * k;
      if (*idum < 0)
        *idum += 2147483647;
      if (j < 32)
        ran1_iv[j] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }
  k = *idum / 127773;
  *idum = 16807 * (*idum - k * 127773) - 2836 * k;
  if (*idum < 0)
    *idum += 2147483647;
  j = ran1_iy / 127773;
  ran1_iy = ran1_iv[j];
  ran1_iv[j] = *idum;
  temp = (ran1_iy) * (1.0 / 2147483647);
  if (temp >= (1.0 - 2.328306e-10))
    return (1.0 - 2.328306e-10);
  else
    return temp;
}