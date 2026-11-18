static int sht21_temp_ticks_to_millicelsius(int val)
{
	val &= ~3;
	return (val * 21965 - 46850) / 10000;
}