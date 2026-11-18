static inline void sync_clear_bit(u32 bit, unsigned long *port)
{
	*port ^= bit;
}