void ComputeReverb16(short *orgPtr,short *destPtr,long xx,long strength)

{
  long valN;
  long valP;
  long temp1;
  long strength_local;
  long xx_local;
  short *destPtr_local;
  short *orgPtr_local;
  
  xx_local = xx;
  destPtr_local = destPtr;
  orgPtr_local = orgPtr;
  while (0 < xx_local) {
    temp1 = (long)*destPtr_local + (strength * *orgPtr_local) / 100;
    if (temp1 < 0x8000) {
      if (temp1 < -0x7fff) {
        temp1 = -0x7fff;
      }
    }
    else {
      temp1._0_2_ = 0x7fff;
    }
    *destPtr_local = (short)temp1;
    xx_local = xx_local + -1;
    destPtr_local = destPtr_local + 1;
    orgPtr_local = orgPtr_local + 1;
  }
  return;
}