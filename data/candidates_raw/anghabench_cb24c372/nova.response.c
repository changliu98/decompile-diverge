static int func0(unsigned char *p)
{
	int ret;

	
	if (*p == 0x73)
		ret = 1;
	else if (*p == 0x88 &&
		 (p[1] == 0x07 || p[1] == 0x08 || (p[1] & 0xf0) == 0xb0 ||
		  (p[1] & 0xf0) == 0xc0))
		ret = 1;
	else
		ret = 0;

	return ret;
}