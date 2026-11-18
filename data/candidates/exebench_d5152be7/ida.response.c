int __cdecl sdram_convert(unsigned int pllin, unsigned int *sdram_freq)
{
  unsigned int tmp; // [rsp+0h] [rbp-18h]

  tmp = ((0x3D09 / (0x3B9ACA00 / pllin)) >> 6) + 1;
  if ( tmp > 0xFF )
    tmp = 255;
  *sdram_freq = tmp;
  return 0;
}