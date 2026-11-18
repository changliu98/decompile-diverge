static inline void func0(u32 *a, u32 *b, int s)
{
	*a &= (1 << s) - 1;
	*b &= (1 << s) - 1;
}