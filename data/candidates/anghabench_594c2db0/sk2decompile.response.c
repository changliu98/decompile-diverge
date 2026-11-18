static inline unsigned REG_A5XX_RB_MRT_BUF_INFO(unsigned idx) {
  unsigned addr;
  addr = (0x0000 + 0x0000) + 0x0000;
  addr += (0x1600 + 0x0000) + (idx * 0x0007);
  return addr;
}