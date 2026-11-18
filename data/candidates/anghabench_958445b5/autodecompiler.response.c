__attribute__((used)) static unsigned int uniphier_gpio_bank_to_reg(unsigned int bank)
{
	unsigned int reg = (bank + 1) * 8;

	/* Uniphier GPIO has 16 banks, but the last 2 banks don't have IRQ mask */
	if (reg >= UNIPHIER_GPIO_IRQ_EN)
		reg += 16;

	return reg;
}