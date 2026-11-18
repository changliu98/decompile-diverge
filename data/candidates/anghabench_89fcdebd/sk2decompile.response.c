static inline unsigned short qla24xx_calc_ct_iocbs(unsigned short ct) {
  unsigned short iocbs = 1;
  if (ct > 2) {
    iocbs = (ct - 2) / 5 + 1;
    if ((ct - 2) % 5) iocbs++;
  }
  return iocbs;
}