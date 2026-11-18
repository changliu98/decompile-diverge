double ran1(long *idum)

{
  int iVar1;
  double temp;
  long k;
  int j;
  long *idum_local;
  double local_10;
  
  if ((*idum < 1) || (ran1::iy == 0)) {
    if (-*idum < 1) {
      *idum = 1;
    }
    else {
      *idum = -*idum;
    }
    for (j = 0x27; -1 < j; j = j + -1) {
      *idum = *idum * 0x41a7 + (*idum / 0x1f31d) * -0x7fffffff;
      if (*idum < 0) {
        *idum = *idum + 0x7fffffff;
      }
      if (j < 0x20) {
        ran1::iv[j] = *idum;
      }
    }
    ran1::iy = ran1::iv[0];
  }
  *idum = *idum * 0x41a7 + (*idum / 0x1f31d) * -0x7fffffff;
  if (*idum < 0) {
    *idum = *idum + 0x7fffffff;
  }
  iVar1 = (int)(ran1::iy / 0x4000000);
  ran1::iy = ran1::iv[iVar1];
  ran1::iv[iVar1] = *idum;
  local_10 = DAT_00102010 * (double)ran1::iy;
  if (DAT_00102008 < local_10) {
    local_10 = DAT_00102008;
  }
  return local_10;
}