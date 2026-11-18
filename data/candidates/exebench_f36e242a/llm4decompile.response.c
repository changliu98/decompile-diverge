int
ltos(char *s, long num)
{
	char buf[20];
	char *p = buf;
	int neg = 0;

	if (num < 0) {
		neg = 1;
		num = -num;
	}
	while (num >= 10) {
		*p++ = '0' + (num % 10);
		num /= 10;
	}
	*p++ = '0' + num;
	if (neg)
		*s++ = '-';
	while (--p >= buf)
		*s++ = *p;
	*s = '\0';
	return 0;
}