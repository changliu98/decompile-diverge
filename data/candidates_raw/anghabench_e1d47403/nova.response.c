static inline uint32_t
func0(uint32_t x, uint32_t y, uint32_t z)
{
	uint32_t a = 0;

	while (x) {
		if (x & 1)
			a ^= y;
		x >>= 1;
		y <<= 1;
		if (y & 0x10000)
			y ^= z;
	}
	return a;
}