int32_t
atomic32_decrement(volatile uint32_t *target)
{
	int32_t result;

	LOCK();
	result = --*target;
	UNLOCK();
	return (result);
}