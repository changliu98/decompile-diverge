int
xchg(volatile uint *addr, uint newval)
{
	uint oldval;

	LOCK();
	oldval = *addr;
	*addr = newval;
	UNLOCK();
	return (oldval);
}