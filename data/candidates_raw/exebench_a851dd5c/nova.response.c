static int func0(unsigned char *p, unsigned long size)
{
	unsigned char c = 0xf;
	unsigned long i = 0;

	while (1) {
		while (i < size) {
			int b = 7;
			while (b >= 0) {
				c <<= 1;
				if (p[0] & (1 << b))
					c |= 1;
				if (c & 0x10)
					c ^= 3;
				b--;
			}
			i++; p++;
		}
		c &= 0xf;
		if (!c)
			break;
		i = 0;
	}
	return c;
}