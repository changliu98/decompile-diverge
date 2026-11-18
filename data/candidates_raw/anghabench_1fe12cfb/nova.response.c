static inline int func0(int idx)
{
	return (idx + 1) & (NR_HASH_ENTRIES - 1);
}