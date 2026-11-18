static inline unsigned REG_A3XX_RB_MRT_BLEND_CONTROL(unsigned index) {
  unsigned ret;
  ret = (0x0000 + 0x20A0 + (index * 4));
  return ret;
}