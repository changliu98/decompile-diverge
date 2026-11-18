int get_sdram_freq(unsigned int pll_in, unsigned int *sdram_freq)
{
  unsigned int tmp;
  tmp = (0x3d09 / (0x3b9ac00 / pll_in)) / 64 + 1;
  if (tmp > 0xff)
    tmp = 0xff;
  *sdram_freq = tmp;
  return 0;
}