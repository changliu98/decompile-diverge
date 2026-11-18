__attribute__((used)) static inline int sht21_temp_ticks_to_millicelsius(int raw_val)
{
	/* Round to lower 2 bits */
	raw_val &= ~0x3;

	return ((raw_val * 22006) >> 13) - 46850;
}