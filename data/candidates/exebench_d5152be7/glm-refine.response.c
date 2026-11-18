define MAX_DIVIDER 255

int __cdecl sdram_convert(unsigned int freq_hz, unsigned int *sdram_freq)
{
  unsigned int divider;

  // Convert frequency from Hz to MHz, then scale by 64 (>> 6) and divide by 15625 (0x3D09).
  // The +1 ensures the divider is rounded up.
  divider = ((15625 / (HZ_PER_MHZ / freq_hz)) >> 6) + 1;

  // Clamp the divider to a maximum of 255 (0xFF)
  if (divider > MAX_DIVIDER)
    divider = MAX_DIVIDER;

  *sdram_freq = divider;
  return 0;
}