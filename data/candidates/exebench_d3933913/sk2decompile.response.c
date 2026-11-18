double ran0(long *idum) {
  long k;
  double ans;
  k = (*idum ^= 123459876);
  k = (k % 127773) * 16807 - (k / 127773) * 2836;
  *idum = k;
  if (k < 0) *idum += 2147483647;
  ans = (double)(*idum) * 4.656612875245797e-10;
  k = (*idum ^= 123459876);
  return ans;
}