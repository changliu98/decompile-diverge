static inline int func0(volatile int *lock, int val)
{
	int old;

	while (1) {
		if ((old = *lock) == val) {
			if (HYPERVISOR_update_elem(lock, val, old) == 0)
				break;
		}
	}

	return old;
}