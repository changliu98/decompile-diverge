static inline void func0(u64 mask, u64 *addr)
{
	*addr &= ~mask;
	*addr &= ~(mask & 0xffffffff00000000ULL);
}