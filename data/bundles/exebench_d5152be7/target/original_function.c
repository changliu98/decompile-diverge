static inline int sdram_convert(unsigned int pllin,unsigned int *sdram_freq)
{
  register unsigned int ns, tmp;

  ns = 1000000000 / pllin;

  tmp = 15625/ns;
  tmp = tmp/64 + 1;
  if (tmp > 0xff) tmp = 0xff;
        *sdram_freq = tmp;

  return 0;

}