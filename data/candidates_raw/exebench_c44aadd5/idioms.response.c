double ran2(long *idum)
{
  int j;
  long k;
  static long ran2_iv[32];
  static long ran2_iy = 0;
  static long ran2_idum2 = 123456789;
  double temp;
  if (*idum <= 0 || *idum == -2147483647 - 1) {
    if (-(*idum) > 1) {
      ran2_idum2 = -(*idum);
    }
    else {
      ran2_idum2 = 1;
    }
    for (j=32 -1; j>=0; j--) {
      ran2_iv[j] = ran2_idum2 / 127773;
      ran2_idum2 = 16807 * (ran2_idum2 % 127773) - 2836 * (ran2_iv[j]);
      if (ran2_idum2 < 0) ran2_idum2 += 2147483563;
      if (j < 31) ran2_iv[j] = ran2_iv[j + 1];
    }
    ran2_iy = ran2_iv[0];
  }
  k = (*idum) / 127773;
  *idum = 16807 * (*idum - k * 127773) - 2836 * k;
  if (*idum < 0) *idum += 2147483563;
  k = ran2_idum2 / 127773;
  ran2_idum2 = 16807 * (ran2_idum2 - k * 127773) - 2836 * k;
  if (ran2_idum2 < 0) ran2_idum2 += 2147483563;
  j = ran2_iy / 127773;
  ran2_iy = ran2_iv[j] - ran2_idum2;
  ran2_iv[j] = *idum;
  if (ran2_iy < 1) ran2_iy += 2147483562;
  ((void) (0));
  temp = (ran2_iy) * (1.0 / 2147483647);
  if (temp >= 0.9999997) return 0.9999997;
  else return temp;
}