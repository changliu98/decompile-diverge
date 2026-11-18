static inline unsigned int atomic_inc(unsigned int *lock)
{
	return __atomic_add_ifless(lock, 1, INT_MAX);
}