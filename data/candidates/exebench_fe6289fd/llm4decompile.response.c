uint8_t
xchg8(uint8_t *ptr, uint8_t x)
{
	uint8_t prev;

	LOCK();
	prev = *ptr;
	*ptr = x;
	UNLOCK();
	return (prev);
}