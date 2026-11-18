int sht21_temp_ticks_to_millicelsius(int ticks)

{
  int ticks_local;
  
  return ((int)((ticks & 0xfffffffcU) * 0x55cd) >> 0xd) + -0xb702;
}