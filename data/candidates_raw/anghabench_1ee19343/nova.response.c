static inline int func0(unsigned long p)
{
	return (p & (PAGE_MASK << 1)) == LOW_PAGE_OFFSET;
}