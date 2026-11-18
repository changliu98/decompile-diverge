double log10(double x)
{
 double ret = 1.0;
 double tmp = 10.0;

 while(1) {
  if(tmp < x) {
   ret += 1.0;
   tmp *= 10.0;
  } else {
   return ret;
  }
 }
}