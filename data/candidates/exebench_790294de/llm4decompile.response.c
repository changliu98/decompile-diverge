void
atomic_or(volatile uintptr_t *x, uintptr_t val)
{
	uintptr_t old, r;

	for (;;) {
		old = *x;
		LOCK();
		if (*x == old) {
			r = old | val;
			*x = r;
			break;
		}
		UNLOCK();
	}
	UNLOCK();
}