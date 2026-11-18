static inline int a_fetch_add(unsigned int *ptr, int delta)
{
	return __atomic_add_ifless(ptr, delta, INT_MAX);
}