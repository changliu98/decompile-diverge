static inline int dac_convert_reg(unsigned int channel)
{
  return (0x70 + (channel & 1) * 2);
}