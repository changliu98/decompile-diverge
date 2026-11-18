unsigned int __cdecl dac_convert_reg(unsigned int channel)
{
  return 2 * (channel & 1) + 112;
}