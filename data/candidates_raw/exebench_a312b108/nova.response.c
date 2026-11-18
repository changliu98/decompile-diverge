static inline unsigned long func0(unsigned long *addr,
						unsigned long val)
{
	unsigned long old = *addr;

	*addr = val;

	return old;
}