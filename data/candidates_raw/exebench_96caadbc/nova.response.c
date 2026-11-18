static inline unsigned long func0(unsigned long *sp,
					     unsigned long *stack)
{
	unsigned long s;

	s = *sp;
	barrier();
	*sp = s + *(s + stack);
	return s;
}