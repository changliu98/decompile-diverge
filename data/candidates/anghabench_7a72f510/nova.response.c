static inline uint32_t gf_poly_mul2(uint32_t x)
{
	return ROT(x, 1) ^ ROT(x, 8) ^ (x >> 7);
}