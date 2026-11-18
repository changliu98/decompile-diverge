static double ran0(long *idum)
{
  long k;
  double ans;
  *idum ^= 0x75BD924;
  k = *idum / 127773;
  *idum = 16807 * (*idum % 127773) - 2836 * k;
  if (*idum < 0) *idum += 2147483647;
  ans = (double)(*idum) * (1.0/2147483647);
  *idum ^= 0x75BD924;
  return ans;
}