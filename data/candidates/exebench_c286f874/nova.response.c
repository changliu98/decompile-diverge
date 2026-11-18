static inline unsigned int fetch_and_add(unsigned int *lock, unsigned int val)
{
	return __atomic_add_return(val, lock);
}