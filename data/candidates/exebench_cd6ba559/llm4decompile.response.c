uintptr_t AddUintptr(uintptr_t *val, uintptr_t delta)
{
	uintptr_t oldval;

	LOCK();
	oldval = *val;
	*val += delta;
	UNLOCK();

	return oldval + delta;
}