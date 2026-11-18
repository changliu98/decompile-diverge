int sdram_convert(unsigned int pllin, unsigned int *sdram_freq)
{
 unsigned int ns;

 ns = (1000000000 / pllin) * 15625;
 ns = (ns >> 6) + 1;

 if (ns > 255)
  ns = 255;

 *sdram_freq = ns;

 return 0;
}