static inline u32 a_swap(u32 *ptr, u32 val)
{
	*(ptr) = val;
	return val;
}