void
atomic_inc(volatile u_int *v)
{
	LOCK();
	(*v)++;
	UNLOCK();
}