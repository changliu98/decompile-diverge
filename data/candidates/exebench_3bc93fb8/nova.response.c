static void bitmap_set(void *state, int c, int len)
{
	unsigned long *s = state;
	unsigned long mask, v, bits;
	int shift;

	mask = (1UL << (len & 63)) - 1;
	v = s[c / 64];
	shift = c % 64;
	bits = 64 - (shift + len);
	v |= (mask << bits);
	while (len >= 64) {
		s[c / 64] = v;
		len -= 64;
		c += 64;
		v = s[c / 64];
		bits = 64 - (c % 64);
		v |= (mask << bits);
	}
	if (len) {
		if (c % 64)
			bits = (64 - (c % 64)) & mask;
		else
			bits = mask + 1;
		bits &= (1UL << len) - 1;
		v |= (bits << bits);
	}
	s[c / 64] = v;
}