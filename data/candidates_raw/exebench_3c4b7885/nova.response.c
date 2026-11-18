static inline void func0(unsigned int nr, unsigned long *addr)
{
	addr[nr >> 5] |= (1UL << (nr & 31));
}