static unsigned int func0(const char *s, unsigned long *res)
{
	unsigned long n = 0;
	unsigned int i = 0;

	while (1) {
		unsigned int c = s[i];
		if (c < '0' || c > '7')
			break;
		c -= '0';
		n <<= 3;
		n += c;
		i++;
	}
	*res = n;
	return i;
}