static inline unsigned REG_DSI_10nm_PHY_LN_CFG1(unsigned dsi_clk_div) {
  unsigned val = 0;
  val |= (dsi_clk_div << 7);
  val |= 0x4;
  return val;
}