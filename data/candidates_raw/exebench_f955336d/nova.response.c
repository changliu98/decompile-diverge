static inline int func0(unsigned int *ptr, int delta)
{
	return __atomic_add_ifless(ptr, delta, INT_MAX);
}