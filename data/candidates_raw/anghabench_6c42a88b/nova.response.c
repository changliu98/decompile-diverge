static inline size_t func0(int count)
{
	size_t size;
	if (count <= 4)
		size = sizeof(u32) + count * sizeof(u32);
	else
		size = sizeof(u32) + 4 * sizeof(u32) +
			(count - 4) * sizeof(u64);
	return size;
}