static inline unsigned REG_A3XX_SP_VS_VPC_DST_REG(unsigned engine) {
  unsigned reg_value;
  reg_value = (0x00001300 + (engine << 2));
  return reg_value;
}