float ran1(long *idum)
{
  int j;
  long k;
  static long ran1_iv[32];
  static long ran1_iy = 0;
  float temp;
  if (*idum <= 0 || !ran1_iy) {
    if (-(*idum) > 1) {
      *idum = -(*idum);
    }
    else {
      *idum = 1;
    }
    for (j=32 -1; j>=0; j--) {
      k = *idum / 127773L;
      *idum = 16807 * (*idum - k * 127773) - 2836 * k;
      if (*idum < 0) *idum += 2147483647L;
      if (j < 32 -1) ran1_iv[j] = *idum;
    }
    ran1_iy = ran1_iv[0];
  }
  k = *idum / 127773L;
  *idum = 16807 * (*idum - k * 127773) - 2836 * k;
  if (*idum < 0) *idum += 2147483647L;
  j = ran1_iy / 127773;
  ran1_iy = ran1_iv[j];
  ran1_iv[j] = *idum;
  temp = (ran1_iy + 0.5) * (1.0 / 2147483648.0);
  if (temp > 0.9999997) return (0.9999997);
  else return (temp);
}