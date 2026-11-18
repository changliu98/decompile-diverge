static inline unsigned int func0(unsigned int x)
{
	unsigned int y = (x & 0xAAAA) >> 1;
	y = (y & 0x5555) + ((y & 0xFF00) >> 2);
	y = (y & 0x3333) + ((y & 0xCC00) >> 4);
	y = (y & 0x0F0F) + ((y & 0xF000) >> 8);
	return y;
}