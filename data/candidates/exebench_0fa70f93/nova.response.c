static inline void atomic_clear_mask(u64 mask, u64 *addr)
{
	*addr &= ~mask;
	*addr &= ~(mask & 0xffffffff00000000ULL);
}