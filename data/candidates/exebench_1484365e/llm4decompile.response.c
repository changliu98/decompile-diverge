uint32_t
atomic32_increment(volatile uint32_t *target)
{
	uint32_t result;

	LOCK();
	result = ++(*target);
	UNLOCK();
	return result;
}