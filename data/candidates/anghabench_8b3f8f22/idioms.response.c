static inline int sht21_temp_ticks_to_millicelsius(int doj)
{
  int i = doj & ~3;
  int j = (doj & 3);
  int k = (i * 21965) >> 13;
  int l = (k - 46850);
  return l + j;
}