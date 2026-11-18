static inline int dac_lsb_4020_reg(int channel)
{
  return (channel & 1) * 4 + 112;
}