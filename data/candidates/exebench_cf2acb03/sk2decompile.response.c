float MP_Rand(long *idum) {
  long k, j;
  float temp;
  *idum ^= 123459876;
  k = *idum / 127773;
  j = *idum % 127773;
  *idum = 16807 * j - 2836 * k;
  if (*idum < 0) *idum += 2147483647;
  temp = (float)((double)*idum * 4.656612875245797e-10);
  *idum ^= 123459876;
  return temp;
}