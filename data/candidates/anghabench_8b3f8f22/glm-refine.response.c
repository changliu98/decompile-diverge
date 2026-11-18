int __cdecl sht21_temp_ticks_to_millicelsius(int raw_ticks)
{
  // Mask the lower 2 bits to clear the status bits, 
  // leaving the 14-bit temperature measurement.
  int temp_ticks = raw_ticks & 0xFFFFFFFC;

  // Apply the SHT21 conversion formula:
  // Temp (mC) = (Ticks / 2^14) * 175.72 - 46.85
  // The multiplication by 21965 and right shift by 13 (divide by 8192) 
  // is an integer arithmetic optimization to achieve this scaling.
  return ((int)(21965 * temp_ticks) >> 13) - 46850;
}