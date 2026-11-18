static inline unsigned REG_A5XX_VPC_SO_BUFFER_OFFSET(unsigned vgt) {
  unsigned location;
  location = (0x0000 + 0x0D000 + (0x3 * vgt));
  return location;
}