static inline unsigned int func0(unsigned int *lock, unsigned int val)
{
	return __atomic_add_return(val, lock);
}