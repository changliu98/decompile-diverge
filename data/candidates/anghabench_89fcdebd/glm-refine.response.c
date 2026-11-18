uint16_t __cdecl qla24xx_calc_ct_iocbs(uint16_t dsds)
{
    if (dsds <= 2)
        return 1;

    uint16_t offset = dsds - 2;
    uint16_t base_iocbs = offset / 5;

    // If there is a remainder, we need an additional IOCB
    if (offset % 5 != 0)
        return base_iocbs + 2;

    return base_iocbs + 1;
}