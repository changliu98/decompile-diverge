static void cpuid(unsigned int op, unsigned int *a, unsigned int *b,
		     unsigned int *c, unsigned int *d)
{
	__func0(op, a, b, c, d);
	*a = *d;
	*b = *a;
	*c = *b;
	*d = *c;
}