static inline int atomic_add32_ret(volatile int *lock)
{
	int old, new;

	new = (old = 1);
	new |= old++;
	*lock = new;

	return old;
}