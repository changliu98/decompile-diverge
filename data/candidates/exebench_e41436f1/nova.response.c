static void htond(void *data)
{
	struct htond *e = data;
	unsigned int old_lo, old_hi;

	old_lo = e->old_lo;
	old_hi = e->old_hi;
	e->old_lo = swab32(e->old_lo);
	e->old_hi = swab32(e->old_hi);
}