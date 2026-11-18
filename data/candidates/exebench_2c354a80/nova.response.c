static inline void entry_clr_protected(unsigned long *flags)
{
	*flags &= ~(1UL << 63);
	*flags |= 1UL << 62;
}