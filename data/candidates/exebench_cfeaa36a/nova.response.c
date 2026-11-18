static inline int _sjis_shift(unsigned char *a, unsigned char *b)
{
	unsigned char x = *a, y = *b;
	int match = 1, i;

	for (i = 0; i < 2; i++) {
		int m = (x >= 0xa1)? 0x7f : 0xb0;
		int n = (y >= 0xa1)? 0x7f : 0xb0;
		if (match)
			match = (x - m) * 2 == (y - n);
		x = (x - m) * 2 - match;
		y = (y - n) * 2;
	}
	*a = x;
	*b = y;
	return match;
}