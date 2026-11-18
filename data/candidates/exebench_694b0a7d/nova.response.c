static inline void dpaa_clear_bits(unsigned long mask, unsigned long *addr)
{
	*addr = *addr & ~mask;
}