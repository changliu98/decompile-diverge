static inline unsigned REG_A3XX_VSC_PIPE_DATA_ADDRESS(unsigned pipe) {
  unsigned reg_value;
  reg_value = (0x0C00 + (pipe * 3));
  return reg_value;
}