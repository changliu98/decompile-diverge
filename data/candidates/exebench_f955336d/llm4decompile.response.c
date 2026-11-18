int
a_fetch_add(volatile int *x, int v)
{
	int r;

	LOCK();
	r = *x;
	*x += v;
	UNLOCK();
	return (r);
}