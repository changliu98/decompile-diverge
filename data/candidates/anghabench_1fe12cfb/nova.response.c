static inline int walNextHash(int idx)
{
	return (idx + 1) & (NR_HASH_ENTRIES - 1);
}