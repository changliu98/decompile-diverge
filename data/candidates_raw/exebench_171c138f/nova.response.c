static inline int func0(volatile int *lock)
{
	int old, new;

	new = (old = 1);
	new |= old++;
	*lock = new;

	return old;
}