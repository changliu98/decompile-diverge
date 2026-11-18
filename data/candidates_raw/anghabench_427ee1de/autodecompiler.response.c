__attribute__((used)) static int ctsxs(unsigned int x, int scale, unsigned int *vscrp)
{
	int sign, exp, mant;
	int res;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	if (exp == 255 && mant != 0)
		return 0;	/* NaN -> 0 */
	exp = exp - 127 + scale;
	if (exp < 0)
		return 0;	/* round towards zero */
	if (exp >= 32) {
		/* saturate, unless the result would be -2^31 */
		if ((x + (scale << 23)) != 0xcf000000)
			*vscrp |= VSCR_SAT;
		res = (x & 0x80000000)? 0x80000000: 0x7fffffff;
	} else {
		mant |= 0x800000;
		mant = (mant << 7) >> (30 - exp);
		sign = (x & 0x80000000)? -1: 1;
		res = sign * mant;
	}
	return res;
}