int uniphier_ld11_get_gpio_muxval(unsigned int pin,
					 unsigned int gpio_offset)
{
	int muxval;

	switch (gpio_offset) {
	case 116: /* XIRQ14 */
	case 119: /* XIRQ17 */
		muxval = 13;
		break;
	case 120: /* XIRQ18 */
	case 121: /* XIRQ19 */
	case 122: /* XIRQ20 */
	case 123: /* XIRQ21 */
	case 124: /* XIRQ22 */
	case 125: /* XIRQ23 */
	case 126: /* XIRQ24 */
	case 127: /* XIRQ25 */
	case 128: /* XIRQ26 */
	case 129: /* XIRQ27 */
	case 130: /* XIRQ28 */
	case 131: /* XIRQ29 */
	case 132: /* XIRQ30 */
	case 133: /* XIRQ31 */
		muxval = 14;
		break;
	default:
		muxval = 15;
		break;
	}

	return muxval;
}