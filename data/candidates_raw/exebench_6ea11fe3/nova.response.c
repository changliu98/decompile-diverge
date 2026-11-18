static inline void func0(int bit, void *addr)
{
	*(u32 *)addr ^= (1 << bit);
}