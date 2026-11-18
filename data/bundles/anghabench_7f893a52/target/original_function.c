int uniphier_ld11_get_gpio_muxval(unsigned int pin,
					 unsigned int gpio_offset)
{
	if (gpio_offset == 132 || gpio_offset == 135)	/* XIRQ12, 15 */
		return 13;

	if (gpio_offset >= 120 && gpio_offset <= 143)	/* XIRQx */
		return 14;

	return 15;
}