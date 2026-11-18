double
ran0(long *idum)
{
 long k;
 double ans;

 *idum ^= 12345678;
 k = (*idum)/127773;
 *idum = 16807*(*idum-k*127773)-k*127773;
 if(*idum < 0)
  *idum += 2147483647;
 ans = (double)*idum*4.656612875e-10;
 *idum ^= 12345678;
 return ans;
}