static char *func0(char *s, long n)
{
	char *p, aux;
	unsigned long m;
	size_t len;

	if (n < 0) {
		m = -n;
	} else {
		m = n;
	}
	p = s;
	do {
		*p++ = m % 10 + '0';
	} while (m /= 10);
	if (n < 0) {
		*p++ = '-';
	}
	len = p - s;
	*p = '\0';

	
	p--;
	while (s < p) {
		aux = *s;
		*s = *p;
		*p = aux;
		s++;
		p--;
	}

	return s - len;
}