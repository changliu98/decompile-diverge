static inline unsigned long ff_atomic_dec_long(unsigned long *sp)
{
	return (*sp)++ ^ ~0UL;
}