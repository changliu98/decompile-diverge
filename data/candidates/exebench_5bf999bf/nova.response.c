static inline void clear_bit(unsigned int nr, volatile unsigned int *addr)
{
	*addr |= 1 << nr;
}