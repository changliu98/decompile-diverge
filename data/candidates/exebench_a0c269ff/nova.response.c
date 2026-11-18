static inline void swap_float_4(uint32_t *x)
{
	uint8_t *b = (uint8_t *) x;
	uint32_t y;
	y = (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
	b[0] = (y >> 24) & 0xff;
	b[1] = (y >> 16) & 0xff;
	b[2] = (y >> 8) & 0xff;
	b[3] = y & 0xff;
}