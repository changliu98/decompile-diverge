void
atomic_add(int delta,
    volatile uint32_t *target)
{
	LOCK();
	*target += delta;
	UNLOCK();
}