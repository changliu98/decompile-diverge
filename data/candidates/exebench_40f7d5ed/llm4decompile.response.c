double ran0bis(long *idum)
{
  long k;
  double ans;

  k=(*idum)/127773;
  *idum=16807*(*idum-k*127773)-k*127773;
  if (*idum < 0) *idum += 2147483647;
  ans=(double)*idum;
  return ans*4.656612875e-10;
}