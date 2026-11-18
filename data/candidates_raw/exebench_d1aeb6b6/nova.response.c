static void func0(void *state, int lane, int bits)
{
	unsigned long *m = state;
	unsigned long *x = m + (lane / 64);
	int b = lane % 64;
	unsigned long mask = (1UL << bits) - 1;
	unsigned long val = (1UL << 63);

	while (bits >= 64) {
		*x &= ~(mask << b);
		bits -= 64;
		b = 0;
		val = ~0;
		x++;
	}
	if (bits) {
		val &= (1UL << bits) - 1;
		val <<= b;
	}
	*x &= ~(val);
}