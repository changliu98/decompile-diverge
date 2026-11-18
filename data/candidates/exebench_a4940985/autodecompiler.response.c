double ran1(long *idum)
{
 int j;
 long k;
 double temp;

 if (*idum <= 0 || !ran1_iy) {
  if (-(*idum) < 1) *idum=1;
  else *idum = -(*idum);
  for(j = 32 + 7; j >= 0; j--) {
   k = (*idum)/127773;
   *idum = 16807*(*idum - k*127773) - k*2836;
   if(*idum < 0) *idum += 2147483647;
   if(j < 32) ran1_iv[j] = *idum;
  }
  ran1_iy = ran1_iv[0];
 }
 k = (*idum)/127773;
 *idum = 16807*(*idum - k*127773) - k*2836;
 if(*idum < 0) *idum += 2147483647;
 j = ran1_iy/(1+(2147483647 -1)/32);
 ran1_iy = ran1_iv[j];
 ran1_iv[j] = *idum;
 if((temp=(1.0/2147483647)*ran1_iy) > (1.0-1.2e-7)) return (1.0-1.2e-7);
 else return temp;
}