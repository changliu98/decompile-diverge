static void set_bit(unsigned char *bitmap, unsigned long pos)
{
	unsigned char mask = 1 << (pos & 7);
	bitmap[pos >> 3] |= mask;
}