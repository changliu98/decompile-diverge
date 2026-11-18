static char *_xtoa(unsigned long n, char *s, int base, int uc)
{
	char *p, aux;
	static const char lowers[] = "0123456789abcdef";
	static const char uppers[] = "0123456789ABCDEF";

	p = s;
	do {
		*(p++) = (uc? uppers[n % base] : lowers[n % base]);
	} while (n /= base);
	*(p++) = '\0';

	
	do {
		aux = *(--p);
		*p = *s;
		*s++ = aux;
	} while (p!= s);
	return s;
}