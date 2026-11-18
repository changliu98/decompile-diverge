uint16_t qla24xx_calc_ct_iocbs(uint16_t dsds)
{
	uint16_t iocbs = 1;

	if (dsds > 2) {
		iocbs += (dsds - 2) / 5;
		if ((dsds - 2) % 5)
			iocbs++;
	}
	return iocbs;
}