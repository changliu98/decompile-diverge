static inline int a_swap(volatile int *lock, int val)
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