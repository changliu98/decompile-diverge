static inline int all_bits_clear(u32 x, u32 y)
{
	return!(x & y) & 1;
}