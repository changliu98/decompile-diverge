static inline u16 BigUnsignedShort(u16 x)
{
	u8 hi = x & 0xff;
	u8 lo = (x & 0xff00) >> 8;
	return (lo << 8) + hi;
}