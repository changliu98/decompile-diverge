int sht21_temp_ticks_to_millicelsius(int raw_measurement)
{
  return ((int)((raw_measurement & 0xfffffffcU) * 0x55cd) >> 0xd) + -0xb702;
}