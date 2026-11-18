static void func0(unsigned char *bitmap, unsigned long pos)
{
	unsigned char mask = 1 << (pos & 7);
	bitmap[pos >> 3] |= mask;
}