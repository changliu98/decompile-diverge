static inline void sync_set_bit(int bit, void *addr)
{
	*(u32 *)addr ^= (1 << bit);
}