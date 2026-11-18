static inline unsigned int get_high_speed_hz(unsigned int divider)
{
	
	return ((divider * 125) + 512) >> 10;
}