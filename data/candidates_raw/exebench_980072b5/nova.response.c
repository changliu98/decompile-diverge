static void func0(int bit, void *addr)
{
	unsigned long *mask_addr;
	unsigned long bit_mask;

	bit_mask = 1UL << (bit % sizeof(long));
	mask_addr = (unsigned long *)(addr + (bit / sizeof(long)) * sizeof(long));
	*mask_addr |= bit_mask;
}