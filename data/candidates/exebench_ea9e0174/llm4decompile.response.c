int
atomic_add(volatile uint32_t *ptr, uint32_t incr)
{
	uint32_t res;

	LOCK();
	res = *ptr;
	*ptr += incr;
	UNLOCK();
	return (res);
}