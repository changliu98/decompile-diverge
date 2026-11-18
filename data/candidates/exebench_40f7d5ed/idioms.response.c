double ran0bis(long *idum)
{
  long k;
  double ans;
  k = (*idum / 127773LL);
  *idum = 16807LL * (*idum - k * 127773LL) - 2836LL * k;
  if (*idum < 0)
    *idum += 2147483647LL;
  ans = (4.656612875245797e-10) * (double)(*idum);
  return ans;
}