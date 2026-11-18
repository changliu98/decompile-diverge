float ran1(long *idum) {
  int j;
  long k;
  float temp;
  if (*idum <= 0 || !iy) {
    if (-(*idum) < 1)
      *idum = 1;
    else
      *idum = -(*idum);
    for (j = 39; j >= 0; j--) {
      k = (*idum) / 127773;
      *idum = 16807 * (*idum - k * 127773) - 2836 * k;
      if (*idum < 0) *idum += 2147483647;
      if (j < 32) iv[j] = *idum;
    }
    iy = iv[0];
  }
  k = (*idum) / 127773;
  *idum = 16807 * (*idum - k * 127773) - 2836 * k;
  if (*idum < 0) *idum += 2147483647;
  j = iy / (1 + (2147483647 - 1) / 32);
  iy = iv[j];
  iv[j] = *idum;
  if ((temp = 1.0 / 2147483563 * (double)iy) > 0.99999988) temp = 0.99999988;
  return temp;
}