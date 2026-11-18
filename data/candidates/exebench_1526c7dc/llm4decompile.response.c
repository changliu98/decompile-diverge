uintptr_t
atomic_and(uintptr_t *x, uintptr_t val)
{
	uintptr_t old, r;

	for (;;) {
		old = *x;
		r = old & val;
		LOCK();
		if (*x == old) {
			*x = r;
			break;
		}
		UNLOCK();
	}
	UNLOCK();
	return (old);
}