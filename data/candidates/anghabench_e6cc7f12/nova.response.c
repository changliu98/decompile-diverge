static inline int aligned(int size)
{
	return (size + 63) >> 6 << 6;
}