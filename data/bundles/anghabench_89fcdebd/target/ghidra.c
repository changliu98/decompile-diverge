uint16_t qla24xx_calc_ct_iocbs(uint16_t dsds)

{
  short sVar1;
  uint16_t iocbs;
  uint16_t dsds_local;
  
  iocbs = 1;
  if (2 < dsds) {
    sVar1 = (short)((int)(dsds - 2) / 5);
    iocbs = sVar1 + 1;
    if ((int)(dsds - 2) % 5 != 0) {
      iocbs = sVar1 + 2;
    }
  }
  return iocbs;
}