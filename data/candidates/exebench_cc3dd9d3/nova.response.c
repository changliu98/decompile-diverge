static void AssignBit(unsigned long *map, int pxm, int val)
{
	unsigned long mask = 1UL << (pxm & 63);

	if (val)
		map[pxm >> 6] |= mask;
	else
		map[pxm >> 6] &= ~mask;
}