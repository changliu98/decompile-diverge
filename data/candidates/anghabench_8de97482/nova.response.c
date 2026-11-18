static inline unsigned int walNextHash(unsigned int i)
{
	return (i + 1) & (NR_CACHE_BLOCKS - 1);
}