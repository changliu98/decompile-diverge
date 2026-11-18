static inline int sjis2jis(unsigned char *a, unsigned char *b)
{
	unsigned char x = *a, y = *b;
	int t1 = (x >= 0xa1), t2 = (y >= 0xa1);
	int d1 = t1? (x - 0xa1) : (x - 0x41);
	int d2 = t2? (y - 0xa1) : (y - 0x41);
	int d = (d1 << 1) - t1 + (d2 << 1) - t2;
	*a = t1? (x - 0x61) : (x - 0x41);
	*b = t2? (y - 0x61) : (y - 0x41);
	return d;
}