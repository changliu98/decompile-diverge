static inline void func0(unsigned long *pfn)
{
	*pfn &= ~(7UL);
	*pfn &= ~(0x100000000UL);
	*pfn |= (3UL);
}