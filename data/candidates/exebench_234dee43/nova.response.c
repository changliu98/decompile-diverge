static const char *utf8_to_ucs4(const char *s, int *value)
{
	unsigned int val = 0;
	int i, j;

	for (i = 0; ; i++) {
		unsigned int c = s[i];
		unsigned int v;

		if ((c & 0x80) == 0) {
			if (value)
				*value = val;
			return s + i;
		}

		if ((c & 0xe0) == 0xc0) {
			v = c & 0x1f;
			i++;
		} else if ((c & 0xf0) == 0xe0) {
			v = c & 0x0f;
			i += 2;
		} else if ((c & 0xf8) == 0xf0) {
			v = c & 0x07;
			i += 3;
		} else if ((c & 0xfc) == 0xf8) {
			v = c & 0x03;
			i += 4;
		} else if ((c & 0xfe) == 0xfc) {
			v = c & 0x01;
			i += 5;
		} else {
			v = 0;
			break;
		}

		val |= (c & 0x3f) << (6 * (3 - v));
		j = v;
		while (--j > 0) {
			c = s[i - j];
			if ((c & 0xc0)!= 0x80)
				break;
			val |= (c & 0x3f) << (6 * (3 - j));
		}
	}
}