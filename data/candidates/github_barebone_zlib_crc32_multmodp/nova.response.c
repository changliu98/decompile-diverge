static inline uint32_t multmodp(uint32_t x, uint32_t y)
{
	uint32_t m, e, w;

	w = (1 << 31);
	m = 0;

	while (1) {
		if (x & w) {
			m ^= y;
			if (~x & (w - 1))
				break;
		} else if (y & w)
			break;
		y >>= 1;
		if (x & w)
			y <<= 1;
		x &= w - 1;
		x <<= 1;
	}

	e = 32;
	while (e-- > 0) {
		if (m & (1 << e))
			m ^= (0x1EDC6F41U << e);
	}

	return m;
}