static inline void func0(unsigned int nr, volatile unsigned int *addr)
{
	*addr |= 1 << nr;
}