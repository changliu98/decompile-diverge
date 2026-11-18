double __cdecl ran0bis(long *idum)
{
  *idum = 16807 * (*idum % 127773) - 2836 * (*idum / 127773);
  if ( *idum < 0 )
    *idum += 0x7FFFFFFFLL;
  return 4.656612875245797e-10 * (double)(int)*idum;
}