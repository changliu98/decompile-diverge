static char *func0(char *s, long n)
{
	char *p, aux;
	unsigned long m;
	size_t len;

	if (n < 0)
		m = -n;
	else
		m = n;
	p = s;
	do {
		*p++ = m % 10 + '0';
	} while (m /= 10);
	if (n < 0)
		*p++ = '-';
	*p = '\0';
	len = p - s;
	p = s;
	while (p < s + len / 2) {
		aux = *p;
		*p = *(s + len - (p - s) - 1);
		*(s + len - (p - s) - 1) = aux;
		p++;
	}
	return s + len - 1;
}