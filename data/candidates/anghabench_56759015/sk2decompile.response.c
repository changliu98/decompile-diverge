static unsigned int dac_convert_reg(unsigned int channel) {
  unsigned int reg;
  reg = 0x70;
  reg += (channel & 0x1) * 2;
  return reg;
}