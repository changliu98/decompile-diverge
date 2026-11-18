static int calc_sdram_freq(unsigned int pll_in, unsigned int *freq)
{
 unsigned int tmp;
 unsigned int div;

 div = 1000000000 / pll_in;
 tmp = 15625 / div;
 tmp = (tmp >> 6) + 1;
 if (tmp > 255)
  tmp = 255;
 *freq = tmp;
 return 0;
}