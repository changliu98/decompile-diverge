static unsigned int qla24xx_calc_ct_iocbs(unsigned int dsds)
{
  unsigned int iocbs = 1;
  if (dsds > 2) {
    iocbs = (dsds - 2) / 5 + 1;
    if ((dsds - 2) % 5)
      iocbs++;
  }
  return iocbs;
}