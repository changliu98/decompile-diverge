void upzero(int dlt,int *dlti,int *bli)

{
  int wd3;
  int wd2;
  int i;
  int *bli_local;
  int *dlti_local;
  int dlt_local;
  
  if (dlt == 0) {
    for (i = 0; i < 6; i = i + 1) {
      bli[i] = (int)((ulong)((long)bli[i] * 0xff) >> 8);
    }
  }
  else {
    for (i = 0; i < 6; i = i + 1) {
      if ((long)dlt * (long)dlti[i] < 0) {
        wd2 = -0x80;
      }
      else {
        wd2 = 0x80;
      }
      bli[i] = wd2 + (int)((ulong)((long)bli[i] * 0xff) >> 8);
    }
  }
  dlti[5] = dlti[4];
  dlti[4] = dlti[3];
  dlti[3] = dlti[2];
  dlti[1] = *dlti;
  *dlti = dlt;
  return;
}