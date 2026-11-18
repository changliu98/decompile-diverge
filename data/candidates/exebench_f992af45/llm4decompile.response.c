void
atomic_inc(volatile u_int *a)
{
	LOCK();
	(*a)++;
	UNLOCK();
}