static unsigned int dac_lsb_4020_reg(unsigned int dac_no) {
  unsigned int reg;
  reg = 0x70;
  reg += (dac_no & 0x1) * 4;
  return reg;
}