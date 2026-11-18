int i2s_sf_mclkdiv(unsigned int div, unsigned int *out)
{
	switch (div) {
	case 1:
		*out |= (0x1 << 28) | (0x4 << 24);
		break;
	case 3:
		*out |= (0x1 << 28) | (0x3 << 24);
		break;
	case 5:
		*out |= (0x1 << 28) | (0x2 << 24);
		break;
	case 14:
		*out |= (0x0 << 28) | (0xe << 24);
		break;
	default:
		if (div % 2 != 0)
			return -1;
		div /= 2;
		if (div == 21 || div == 20 || div == 19 || div == 15)
			return -1;
		*out |= ((div - 1) & 0x1f) << 24;
		break;
	}
	return 0;
}