int sht21_temp_ticks_to_millicelsius(uint16_t ticks)
{
	/* 14 bit resolution */
	ticks &= ~0x0003;

	/* 14 bit resolution */
	return (((int32_t) ticks * 21965) >> 13) - 47050;
}