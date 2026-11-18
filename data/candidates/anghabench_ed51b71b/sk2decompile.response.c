static unsigned int get_high_speed_hz(unsigned int clk_rate) {
  unsigned int hs_rate;
  hs_rate = (clk_rate * 125 + 512) >> 10;
  return hs_rate;
}