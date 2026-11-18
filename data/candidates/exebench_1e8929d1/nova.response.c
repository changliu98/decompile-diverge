static void convert2ASCII(char c, char *s)
{
	unsigned char val = (unsigned char) c;
	unsigned char high = (val >> 4) & 0x0F;

	if (high < 10)
		s[0] = '0' + high;
	else
		s[0] = 'a' + high - 10;

	val &= 0x0F;
	if (val < 10)
		s[1] = '0' + val;
	else
		s[1] = 'a' + val - 10;
}