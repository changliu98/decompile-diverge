static int func0(unsigned int pin,
					 unsigned int gpio_offset)
{
	int port;

	switch (gpio_offset) {
	case MV88E6063_GPIO_PORT_1:
	case MV88E6063_GPIO_PORT_2:
	case MV88E6063_GPIO_PORT_3:
	case MV88E6063_GPIO_PORT_4:
	case MV88E6063_GPIO_PORT_5:
	case MV88E6063_GPIO_PORT_6:
		port = 13;
		break;
	case MV88E6063_GPIO_PORT_1_MIRROR:
	case MV88E6063_GPIO_PORT_2_MIRROR:
	case MV88E6063_GPIO_PORT_3_MIRROR:
	case MV88E6063_GPIO_PORT_4_MIRROR:
	case MV88E6063_GPIO_PORT_5_MIRROR:
	case MV88E6063_GPIO_PORT_6_MIRROR:
		port = 14;
		break;
	default:
		port = 15;
		break;
	}

	return port;
}