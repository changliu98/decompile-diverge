static unsigned int uniphier_gpio_bank_to_reg(unsigned int secs)
{
	unsigned int val;

	val = (secs + 1) * 8;
	if (val > SLP_RATE_MAX)
		val = SLP_RATE_MAX + 0x10;
	return val;
}