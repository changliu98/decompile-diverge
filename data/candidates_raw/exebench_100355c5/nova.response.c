static const char *func0(const char *s, long *v)
{
	int c;
	int sign = 0;

	c = *s++;
	if (c == '-') {
		sign = 1;
		c = *s++;
	}
	else if (c == '+')
		c = *s++;
	if (!('0' <= c && c <= '9'))
		*v = 0;
	else
		for (*v = 0; '0' <= c && c <= '9'; c = *s++)
			*v = *v * 10 + c - '0';
	if (sign)
		*v = -*v;
	return s;
}