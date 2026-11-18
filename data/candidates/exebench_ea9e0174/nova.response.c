static inline unsigned int atomic_add(unsigned int *lock, unsigned int val)
{
	return __atomic_add_return(val, lock);
}