uint16_t __cdecl qla24xx_calc_ct_iocbs(uint16_t dsds)
{
  uint16_t iocbs; // [rsp+0h] [rbp-4h]

  iocbs = 1;
  if ( dsds > 2u )
  {
    iocbs = (dsds - 2) / 5 + 1;
    if ( (dsds - 2) % 5 )
      return (dsds - 2) / 5 + 2;
  }
  return iocbs;
}