static inline void validate_st_entry(unsigned long *sp)
{
	*sp &= ~0x3;		
	*sp |= (0 << 2);	
}