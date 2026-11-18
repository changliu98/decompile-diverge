static void func0(u8 c, u8 *data)
{
	u8 mask = 0x80;
	u8 *ptr = data;
	int i;

	for (i = 0; i < 8; i++) {
		*ptr = (mask & c)? 1 : 0;
		c <<= 1;
		ptr++;
	}
}