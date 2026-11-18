double ran0bis(long *idum) {
  long k;
  double ans;
  k = *idum / 127773;
  *idum = 16807 * (*idum - k * 127773) - 2836 * k;
  if (*idum < 0) *idum += 2147483647;
  ans = (double)(*idum) * 4.656612875245797e-10;
  return ans;
}