double ran0(long *idum)

{
  double dVar1;
  double ans;
  long k;
  long *idum_local;
  
  *idum = *idum ^ 0x75bd924;
  *idum = *idum * 0x41a7 + (*idum / 0x1f31d) * -0x7fffffff;
  if (*idum < 0) {
    *idum = *idum + 0x7fffffff;
  }
  dVar1 = DAT_00102008 * (double)*idum;
  *idum = *idum ^ 0x75bd924;
  return dVar1;
}