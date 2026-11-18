static inline uint32_t func0(uint32_t x)
{
	return ROT(x, 1) ^ ROT(x, 8) ^ (x >> 7);
}