void
atomic_dec(volatile u_int *v)
{
	LOCK();
	*v--;
	UNLOCK();
}