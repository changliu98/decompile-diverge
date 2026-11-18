int __cdecl sht21_temp_ticks_to_millicelsius(int ticks)
{
  return ((int)(21965 * (ticks & 0xFFFFFFFC)) >> 13) - 46850;
}