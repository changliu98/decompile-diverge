static inline void set_bit(unsigned int nr, unsigned long *addr)
{
	addr[nr >> 5] |= (1UL << (nr & 31));
}