static inline unsigned REG_A4XX_RB_MRT_CONTROL(unsigned idx) {
  unsigned ret;
  ret = (0x0000 + 0x20AC) + (idx * 0x5);
  return ret;
}