static inline unsigned REG_A4XX_RB_MRT_BUF_INFO(unsigned idx) {
  unsigned reg;
  reg = (0x0000 + 0x2065);
  reg += (idx * 0x5);
  return reg;
}