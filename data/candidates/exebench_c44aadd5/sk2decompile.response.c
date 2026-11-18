float ran2(long *idum) {
  int j;
  long k;
  float temp;
  if (*idum <= 0) {
    if (-(*idum) < 1)
      *idum = 1;
    else
      *idum = -(*idum);
    iy = *idum;
    for (j = 39; j >= 0; j--) {
      k = (*idum) / 53668;
      *idum = 40014 * (*idum - k * 53668) - k * 12211;
      if (*idum < 0) *idum += 2147483563;
      if (j < 32) iv[j] = *idum;
    }
    iytemp = iv[0];
  }
  k = (*idum) / 53668;
  *idum = 40014 * (*idum - k * 53668) - k * 12211;
  if (*idum < 0) *idum += 2147483563;
  k = iy / 52774;
  iy = 40692 * (iy - k * 52774) - k * 3791;
  if (iy < 0) iy += 2147483399;
  j = iytemp / (1 + (2147483562 - 1) / 32);
  iytemp = iv[j] - iy;
  iv[j] = *idum;
  if (iytemp < 1) iytemp += 2147483562;
  if ((temp = 1.0 / 2147483563 * (double)iytemp) > 0.9999997)
    temp = 0.9999997;
  return temp;
}