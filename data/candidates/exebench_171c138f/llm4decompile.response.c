uint32_t
atomic_add32_ret(volatile uint32_t *cnt)
{
	uint32_t ret;

	LOCK();
	ret = *cnt;
	*cnt = ret + 1;
	UNLOCK();
	return (ret);
}