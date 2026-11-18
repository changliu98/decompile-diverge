int i2s_sf_sclkdiv(unsigned int div, unsigned int *config)
{
	unsigned int div_reg;

	if (div == 1) {
		div_reg = 0;
		*config |= (1 << 23);
	} else if (div == 3) {
		div_reg = 0;
		*config |= (1 << 23) | (1 << 20);
	} else if (div % 2 != 0) {
		return -1;
	} else {
		div_reg = (div / 2) - 1;
		if (div_reg == 9 || div_reg == 10)
			return -1;
		*config |= (div_reg & 0xf) << 20;
	}

	return 0;
}