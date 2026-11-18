void atomic_clear_mask(unsigned long mask, atomic_t *addr)
{
	unsigned long oldval, newval;

	do {
		oldval = addr->counter;
		newval = oldval & ~mask;
	} while (!atomic_cmpxchg((atomic_t *) &addr->counter, oldval, newval));
}