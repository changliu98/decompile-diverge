int
a_swap(int *p, int v)
{
	int old;

	LOCK();
	old = *p;
	*p = v;
	UNLOCK();
	return (old);
}