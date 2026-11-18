static inline unsigned REG_A5XX_RB_MRT(unsigned idx) {
  unsigned addr;
  addr = (0xE000 + idx * 0x7);
  return addr;
}