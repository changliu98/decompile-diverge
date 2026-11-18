static size_t __reverse_ffs(size_t num)
{
	int bits = 0;

	if ((num & 0xffff0000) == 0)
		bits += 16, num >>= 16;
	if ((num & 0xff00) == 0)
		bits += 8, num >>= 8;
	if ((num & 0xf0) == 0)
		bits += 4, num >>= 4;
	if ((num & 0xc) == 0)
		bits += 2, num >>= 2;
	if ((num & 0x2) == 0)
		bits += 1, num >>= 1;
	return bits;
}