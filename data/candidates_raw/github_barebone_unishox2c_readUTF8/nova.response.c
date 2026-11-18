static int func0(const char *s, int n, int i, int *nbytes)
{
	int c;

	c = 0;
	for (;;) {
		if (i >= n - 1 || (s[i] & 0x80)!= 0x80 ||
		    (s[i + 1] & 0xc0)!= 0xc0 ||
		    (s[i + 2] & 0xc0)!= 0xc0 ||
		    (s[i + 3] & 0xc0)!= 0xc0)
			break;
		c = s[i] & 0x1f;
		c <<= 6;
		c += s[i + 1] & 0x3f;
		c <<= 6;
		c += s[i + 2] & 0x3f;
		c <<= 6;
		c += s[i + 3] & 0x3f;
		if (c >= 0xd800 && c <= 0xdfff)
			c = 0;
		i += 4;
	}
	*nbytes = i;
	return c;
}