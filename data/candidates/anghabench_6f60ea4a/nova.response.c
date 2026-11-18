static unsigned int denormal_addf1(unsigned int x, unsigned int y)
{
	unsigned int exp, s, z;

	if (x < 0x01000000) {
		z = x + y;
	} else {
		s = x & 0x7fffffff;
		exp = (s >> 23) - 127;
		if (exp < 31) {
			z = x;
		} else {
			s = y & 0x7fffffff;
			exp = (s >> 23) - 127;
			if (exp < 31) {
				z = y;
			} else {
				s = x & 0x7fffffff;
				s |= y & 0x80000000;
				s += 0x00800000;
				if (s > 0x7f800000) {
					s >>= 1;
					exp++;
				}
				z = s & 0x7fffffff;
				z |= exp << 23;
			}
		}
	}
	return z;
}