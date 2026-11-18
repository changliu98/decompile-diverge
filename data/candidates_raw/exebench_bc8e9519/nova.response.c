static void func0(int bit, void *data)
{
	unsigned long *addr;
	u32 mask;

	mask = 1UL << (bit % 32);
	addr = (unsigned long *)(data + (bit / 32) * sizeof(unsigned long));
	*addr |= mask;
}