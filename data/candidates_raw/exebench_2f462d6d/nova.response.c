static int func0(char *buf, int val)
{
	buf[0] = val & 0xff;
	buf[1] = val >> 8;
	return val;
}