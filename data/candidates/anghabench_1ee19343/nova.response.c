static inline int is_ioat_suspended(unsigned long p)
{
	return (p & (PAGE_MASK << 1)) == LOW_PAGE_OFFSET;
}