static inline void func0(u32 *a, u32 *b, int n)
{
	*a &= (1 << n) - 1;
	*b &= (1 << n) - 1;
}