static void func0(char *buf, unsigned char val)
{
	const char *hex = "0123456789ABCDEF";

	buf[0] = hex[(val >> 4) & 0xF];
	buf[1] = hex[val & 0xF];
	buf[2] = 0;
}