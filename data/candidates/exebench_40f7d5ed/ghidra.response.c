double ran0bis(long *idum)

{
  double ans;
  long k;
  long *idum_local;
  
  *idum = *idum * 0x41a7 + (*idum / 0x1f31d) * -0x7fffffff;
  if (*idum < 0) {
    *idum = *idum + 0x7fffffff;
  }
  return DAT_00102008 * (double)*idum;
}