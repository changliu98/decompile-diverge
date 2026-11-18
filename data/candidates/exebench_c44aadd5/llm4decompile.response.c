float ran2(long *idum)
{
 int j;
 long k;
 float temp;

 if (*idum <= 0) {
  if (-(*idum) < 1) *idum=1;
  else *idum = -(*idum);
  ran2::idum2=(long)(*idum);
  for (j=40 -1;j>=0;j--) {
   k=(*idum)/127773;
   *idum=16807*(*idum-k*127773)-k*2836;
   if (*idum < 0) *idum += 2147483647;
   if (j < 32) ran2::iv[j] = *idum;
  }
  ran2::iy=ran2::iv[0];
 }
 k=(*idum)/127773;
 *idum=16807*(*idum-k*127773)-k*2836;
 if (*idum < 0) *idum += 2147483647;
 k=ran2::idum2/53234;
 ran2::idum2=3791*ran2::idum2-k*53234;
 if (ran2::idum2 < 0) ran2::idum2 += 100001001;
 j=ran2::iy/(1+(2147483647 -1)/32);
 ran2::iy=ran2::iv[j]-ran2::idum2;
 ran2::iv[j] = *idum;
 if (ran2::iy < 1) ran2::iy += 2147483647;
 temp=(float)ran2::iy*4.656613057E-10;
 if (temp > (1.0-1.2e-30)) return (1.0-1.2e-30);
 else return temp;
}