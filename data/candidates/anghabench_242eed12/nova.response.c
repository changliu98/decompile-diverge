static inline u16 wacom_intuos_id_mangle(u16 a)
{
	return ((a & 0xfff0) << 4) | (a & 0x000f);
}