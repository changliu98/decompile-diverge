static inline unsigned long XXH_swap64(unsigned long x)
{
	return  ((x & (unsigned long)0x00000000000000ffUL) << 56) |
		((x & (unsigned long)0x000000000000ff00UL) <<  40) |
		((x & (unsigned long)0x0000000000ff0000UL) <<  24) |
		((x & (unsigned long)0x00000000ff000000UL) <<  8)  |
		((x & (unsigned long)0x000000ff00000000UL) >>  8)  |
		((x & (unsigned long)0x0000ff0000000000UL) >> 24)  |
		((x & (unsigned long)0x00ff000000000000UL) >> 40)  |
		((x & (unsigned long)0xff00000000000000UL) >> 56);
}