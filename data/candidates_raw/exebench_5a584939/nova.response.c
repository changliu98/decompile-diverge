static inline u8 func0(u8 *sense_data, u8 mask)
{
	sense_data[0] &= ~0x0e;
	sense_data[0] |= mask & 0x0e;
	return sense_data[0];
}