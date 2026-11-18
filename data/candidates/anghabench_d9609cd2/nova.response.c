static inline u32 reassemble_21(u32 c)
{
	return (c & 0x100000) |
		((c & 0xf800) << 7) |
		((c & 0x7e0) << 14) |
		((c & 0x10) << 20) |
		((c & 0x7) << 24);
}