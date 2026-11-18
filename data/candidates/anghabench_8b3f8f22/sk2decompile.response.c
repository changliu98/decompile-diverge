static int sht21_temp_ticks_to_millicelsius(int t) {
  int temp;
  t &= ~0x03;
  temp = (175 * t) >> 13;
  temp -= 46850;
  return temp;
}