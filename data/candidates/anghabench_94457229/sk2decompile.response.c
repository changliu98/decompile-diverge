static inline unsigned int clk_div_even_up(unsigned int div) {
  if (div == 1)
    return 1;
  else
    return (div + 1) & ~1;
}