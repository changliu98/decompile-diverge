static inline int func0(unsigned int *lock)
{
	int owner = (int)atomic_add_return(-1, (atomic_t *)lock) - 1;
	return owner;
}