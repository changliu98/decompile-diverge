static inline void func0(unsigned long *flags)
{
	*flags &= ~(1UL << 63);
	*flags |= 1UL << 62;
}