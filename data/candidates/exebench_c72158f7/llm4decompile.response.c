double rnd(unsigned long *idum)
{
 long k;
 double ans;






 k=(*idum)/128;
 *idum=25365*(*idum-k*128)+k;
 if(*idum<0) *idum+=32768;
 ans=(double)*idum/32768.0;
 return ans;
}