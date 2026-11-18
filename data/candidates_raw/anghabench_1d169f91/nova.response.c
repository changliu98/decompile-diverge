static int func0(unsigned char c1, unsigned char c2, unsigned char *c3)
{
	if (c1 == 0 || c1 == 6)
		c3[0] = (c2 << 7) | 0x0f;
	else if (c1 == 11)
		c3[0] = (c2 << 7) | 0x7f;
	else
		c3[0] = (c1 << 7) | 0x0f;
	c3[1] = 0xf0 | (c1 & 0xf);
	c3[2] = 0xff;
	return 3;
}