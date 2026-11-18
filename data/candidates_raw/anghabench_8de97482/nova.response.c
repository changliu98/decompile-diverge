static inline unsigned int func0(unsigned int i)
{
	return (i + 1) & (NR_CACHE_BLOCKS - 1);
}