static inline unsigned int func0(unsigned int *lock)
{
	return __atomic_add_ifless(lock, 1, INT_MAX);
}