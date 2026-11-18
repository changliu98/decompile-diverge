static int _safe_calloc_check_mul(unsigned long a, unsigned long b, unsigned long *r)
{
	unsigned long n;

	if (r) {
		n = a;
	} else {
		n = r = a;
	}

	n %= b;

	if (r)
		*r = n;

	return n? 1 : 0;
}