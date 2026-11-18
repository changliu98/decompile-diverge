static int func0(u64 *value, const u8 *buf)
{
	const u8 *p = buf;
	int i;

	switch (p[0]) {
	case 0x00:
		*value = (p[0] & 0x0f) << 6;
		i = 1;
		break;
	case 0x80:
		*value = (p[0] & 0x1f) << 6;
		i = 1;
		break;
	case 0xc0:
		*value = (p[0] & 0x0f) << 6;
		i = 2;
		break;
	case 0xe0:
		*value = (p[0] & 0x0f) << 6;
		i = 3;
		break;
	case 0xf0:
		*value = (p[0] & 0x07) << 6;
		i = 4;
		break;
	case 0xf8:
		*value = (p[0] & 0x03) << 6;
		i = 5;
		break;
	case 0xfc:
		*value = (p[0] & 0x01) << 6;
		i = 6;
		break;
	default:
		i = 0;
	}

	return i;
}