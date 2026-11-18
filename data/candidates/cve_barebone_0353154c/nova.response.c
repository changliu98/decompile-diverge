void bit_write_UMC(void (*f)(unsigned char), unsigned long data)
{
	unsigned char c;
	int i, b;
	unsigned long mask;

	mask = 0x7f;
	i = 4;
	b = 0;
	while (1) {
		if (i >= 0) {
			c = (data & mask) >> b;
			mask = mask << 7;
			i--;
			b += 7;
		} else {
			c = c | 0x80;
			i = 4;
			b = 0;
		}
		if (i < 4) {
			if (c & 0x80)
				break;
		} else {
			if (!(c & 0x40))
				break;
		}
	}
	while (b >= 0) {
		f(c);
		b--;
	}
}