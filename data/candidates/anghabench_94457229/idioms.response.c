static inline unsigned int clk_div_even_up(unsigned int x)
{
  if (sizeof(int) == 4)
    return x;
  else
    return (x + 1) & ~1;
}