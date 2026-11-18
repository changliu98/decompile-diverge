float ran2(long *idum)

{
  int iVar1;
  float temp;
  long k;
  int j;
  long *idum_local;
  float local_c;
  
  if (*idum < 1) {
    if (-*idum < 1) {
      *idum = 1;
    }
    else {
      *idum = -*idum;
    }
    ran2::idum2 = *idum;
    for (j = 0x27; -1 < j; j = j + -1) {
      *idum = *idum * 0x9c4e + (*idum / 0xd1a4) * -0x7fffffab;
      if (*idum < 0) {
        *idum = *idum + 0x7fffffab;
      }
      if (j < 0x20) {
        ran2::iv[j] = *idum;
      }
    }
    ran2::iy = ran2::iv[0];
  }
  *idum = *idum * 0x9c4e + (*idum / 0xd1a4) * -0x7fffffab;
  if (*idum < 0) {
    *idum = *idum + 0x7fffffab;
  }
  ran2::idum2 = (ran2::idum2 % 0xce26) * 0x9ef4 + (ran2::idum2 / 0xce26) * -0xecf;
  if (ran2::idum2 < 0) {
    ran2::idum2 = ran2::idum2 + 0x7fffff07;
  }
  iVar1 = (int)(ran2::iy / 0x3fffffe);
  ran2::iy = ran2::iv[iVar1] - ran2::idum2;
  ran2::iv[iVar1] = *idum;
  if (ran2::iy < 1) {
    ran2::iy = ran2::iy + 0x7fffffaa;
  }
  local_c = (float)(DAT_00102010 * (double)ran2::iy);
  if (DAT_00102008 < (double)local_c) {
    local_c = DAT_00102028;
  }
  return local_c;
}