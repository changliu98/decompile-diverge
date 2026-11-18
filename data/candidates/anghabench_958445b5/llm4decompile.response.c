u32 uniphier_gpio_bank_to_reg(unsigned int bank)
{
	u32 reg = (bank + 1) * 8;

	if (reg >= UNIPHIER_GPIO_IRQ_EN)
		reg += 16;

	return reg;
}