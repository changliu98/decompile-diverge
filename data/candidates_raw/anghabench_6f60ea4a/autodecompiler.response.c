__attribute__((used)) static unsigned int denormalize(unsigned int x, unsigned int lsb)
{
	int exp;
	unsigned int frac;

	if (x < 0x00800000U)
		return x + lsb;
	exp = (x & 0x7f800000U) >> 23;
	if (exp - 1 > 31)
		return x;	/* Inf or NaN */
	lsb >>= exp - 1;
	if (!lsb)
		return x;	/* no rounding required */
	frac = (x & 0x007fffffU) | 0x00800000U;
	frac += lsb;
	if (frac >= 0x01000000U) {
		/* propagate carry from low to high */
		frac >>= 1;
		exp++;
	}
	return (exp << 23) | (frac & 0x007fffffU);
}