static inline void endian_swap16bit(ushort * p)
{
	*p = (*p & 0x00ff) << 8 | (*p & 0xff00) >> 8;
}