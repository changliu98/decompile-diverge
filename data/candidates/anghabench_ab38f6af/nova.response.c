static inline u16 ad7192_get_temp_scale(int id)
{
	return id? 0xb15 : 0xb05;
}