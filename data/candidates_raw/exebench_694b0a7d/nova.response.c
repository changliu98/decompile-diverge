static inline void func0(unsigned long mask, unsigned long *addr)
{
	*addr = *addr & ~mask;
}