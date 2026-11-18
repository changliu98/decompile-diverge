static inline void _crc32_final(u32 *v)
{
	*v = *v ^ 0xFFFFFFFF;
}