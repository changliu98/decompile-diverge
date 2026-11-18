static void clear_bit(int nr, void *addr)
{
	unsigned long mask;
	unsigned long *p;

	mask = 1UL << (nr & 63);
	p = (unsigned long *)addr + (nr >> 6);
	*p &= ~mask;
}