static char *
itoa(long value, char *ptr, int radix)
{
	char buf[37], *p, *s;

	static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	s = p = buf + sizeof buf;
	if (value == 0)
		*--p = '0';
	else
		for (; value; value /= radix)
			*--p = digits[value % radix];
	if (radix == 10 && value < 0)
		*--p = '-';
	for (; p < s; p++, ptr++) {
		*ptr = *p;
		if (p < --s)
			*p = '\0';
	}
	*ptr = '\0';
	return (p);
}