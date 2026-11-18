static inline unsigned long ihk_atomic_add_long_return(unsigned long *sp,
					     unsigned long *stack)
{
	unsigned long s;

	s = *sp;
	barrier();
	*sp = s + *(s + stack);
	return s;
}