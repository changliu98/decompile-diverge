double __cdecl ran0(long *idum)
{
  double ans; // [rsp+0h] [rbp-18h]

  *idum ^= 0x75BD924uLL;
  *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
  if ( *idum < 0 )
    *idum += 0x7FFFFFFFLL;
  ans = 4.656612875245797e-10 * (double)(int)*idum;
  *idum ^= 0x75BD924uLL;
  return ans;
}