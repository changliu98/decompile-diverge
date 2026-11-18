void
a_or(volatile int *p, int v)
{
	LOCK();
	*p |= v;
	UNLOCK();
}