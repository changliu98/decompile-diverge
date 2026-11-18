unsigned char btcl_reg(unsigned int reg, int bit, unsigned int *reg_val) {
  unsigned char ret;
  ret = (reg & (1 << bit)) ? 1 : 0;
  *reg_val = reg;
  return ret;
}