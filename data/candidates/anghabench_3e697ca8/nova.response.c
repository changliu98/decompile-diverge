static unsigned int swizzle(unsigned int val, unsigned int base)
{
	unsigned int fac, res = 0;
	for (fac = 1; base; fac <<= 1, base >>= 1) {
		if (val & 1)
			res |= fac;
		val >>= 1;
	}
	return res;
}