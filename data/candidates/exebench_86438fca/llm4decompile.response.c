int
atomic_sub(volatile u_int *v, int a)
{
	int val;

	LOCK();
	val = *v;
	*v -= a;
	UNLOCK();
	return (val);
}