static int ctsxs(unsigned int x, int scale, unsigned int *r)
{
	unsigned int y;
	int exp, mant;

	exp = (x >> 23) & 0xff;
	mant = x & 0x7fffff;
	if (exp == 255 && mant!= 0)
		return 0;		
	exp = exp - 127 + scale;
	if (exp < 0)
		return 0;		
	if (exp >= 32) {
		
		if (x + (scale << 23)!= 0xcf000000)
			*r |= SCALE_SWITCH_TRAP;
		return (x & 0x80000000)? 0xffffffff : 0x7fffffff;
	}
	mant |= 0x800000;
	mant = (mant << 7) >> (31 - exp);
	if (x & 0x80000000)
		y = -mant;
	else
		y = mant;
	y = (y & 0x7fffffff) + 1;
	return y;
}