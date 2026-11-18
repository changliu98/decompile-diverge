static inline unsigned REG_A4XX_SP_DS_VPC_DST_REG(unsigned index) {
  unsigned location;
  location = (0x00000FC0 + (index << 2));
  return location;
}