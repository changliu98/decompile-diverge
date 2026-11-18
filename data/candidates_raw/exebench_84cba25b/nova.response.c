static char *func0(char *wrptr, u8 reg)
{
	*wrptr++ = reg / 91 + 0x21;
	*wrptr++ = reg % 91 + 0x21;
	return wrptr;
}