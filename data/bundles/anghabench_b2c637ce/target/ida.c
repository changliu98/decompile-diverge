unsigned int __cdecl dac_lsb_4020_reg(unsigned int channel)
{
  return 4 * (channel & 1) + 112;
}