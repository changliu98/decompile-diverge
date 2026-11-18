static inline void func0(ushort * p)
{
	*p = (*p & 0x00ff) << 8 | (*p & 0xff00) >> 8;
}