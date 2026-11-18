static inline void dpaa_set_bits(u32 v, u32 *addr)
{
	*addr = *addr | v;
}