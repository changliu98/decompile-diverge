__attribute__((used)) static void
triggers_bug(struct spinlock *lck)
{

#if defined(__i386__) || defined(__amd64__)
	unsigned int old, new;

	do {
		old = lck->thr_spinlock;
		new = old + 1;
		if (old == 0xffffffff)
			new = 1;
	} while (__sync_val_compare_and_swap(&lck->thr_spinlock, old, new) != old);
#elif defined(__sparc64__)
	unsigned long old, new, addr;

	addr = (unsigned long)&lck->thr_spinlock;
	do {
		old = *(unsigned long *)addr;
		new = old + 1;
		if (old == 0xffffffff)
			new = 1;
	} while (atomic_cas_64(addr, old, new) != old);
#else
	int old, new;

	do {
		old = lck->thr_spinlock;
		new = old + 1;
		if (old == 0xffffffff)
			new = 1;
	} while (_thr_atomic_cmpset_int(&lck->thr_spinlock, old, new) != old);
#endif
}