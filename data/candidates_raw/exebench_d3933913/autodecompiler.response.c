double ran1(long *idum)
{
 long k;
 double ans;

 *idum ^= 123459876;
 k = (*idum)/127773;
 *idum = 16807*(*idum-k*127773)-2836*k;
 if (*idum < 0) *idum += 2147483647;
 ans = (1.0/2147483647)*(*idum);
 *idum ^= 123459876;
 return ans;
}