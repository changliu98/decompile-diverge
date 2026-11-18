unsigned int uniphier_gpio_bank_to_reg(unsigned int bank)
{
	unsigned int reg;

	reg = (bank + 1) * 8;

	/*
	 * Unfortunately, the GPIO port registers are not contiguous because
	 * offset 0x90-0x9f is used for IRQ.  Add 0x10 when crossing the region.
	 */
	if (reg >= UNIPHIER_GPIO_IRQ_EN)
		reg += 0x10;

	return reg;
}