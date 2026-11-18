static void png_64bit_product(uint32_t a, uint32_t b, uint32_t *highp, uint32_t *lowp)
{
	uint32_t a0 = a & 0xffff;
	uint32_t a1 = a >> 16;
	uint32_t b0 = b & 0xffff;
	uint32_t b1 = b >> 16;
	uint32_t z0 = a0 * b0;
	uint32_t z1 = a0 * b1;
	uint32_t z2 = a1 * b0;
	uint32_t z3 = a1 * b1;
	uint32_t z4 = z2 + z1;
	uint32_t z5 = z4 + z3;

	*lowp = (z0 & 0xffff) + ((z4 & 0xffff) << 16);
	*highp = (z0 >> 16) + (z2 & 0xffff) + (z5 >> 16);
}