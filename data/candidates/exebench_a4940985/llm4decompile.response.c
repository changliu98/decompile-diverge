double ran1(long *idum)
{
 int j;
 long k;
 double temp;

 if (*idum <= 0 || !ran1::iy) {
  if (-(*idum) < 1) *idum=1;
  else *idum = -(*idum);
  for (j=39;j>=0;j--) {
   k=(*idum)/127773;
   *idum=16807*(*idum-k*127773)-k*127773;
   if (*idum < 0) *idum += 2147483647;
   if (j < 32) ran1::iv[j] = *idum;
  }
  ran1::iy=ran1::iv[0];
 }
 k=(*idum)/127773;
 *idum=16807*(*idum-k*127773)-k*127773;
 if (*idum < 0) *idum += 2147483647;
 j=ran1::iy/(1+(2147483647 -1)/32);
 ran1::iy=ran1::iv[j];
 ran1::iv[j] = *idum;
 temp=(1.0/2147483647)*ran1::iy;
 if (temp > (1.0-1.2e-7)) return (1.0-1.2e-7);
 else return temp;
}