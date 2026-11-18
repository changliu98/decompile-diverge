static inline unsigned long atomic_fetch_xor(unsigned long *addr,
						unsigned long val)
{
	unsigned long old = *addr;

	*addr = val;

	return old;
}